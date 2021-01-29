
// // This is the command sequence that initialises the ILI9341 driver
// //
// // This setup information uses simple 8 bit SPI writecommand() and writedata() functions
// //
// // See ST7735_Setup.h file for an alternative format
/*
#define TFT_CMD_DELAY	0x80
{
    static const uint8_t ILI9342_init[] = {
        16,                   					        // 22 commands in list
        0xC8, 3, 0xFF, 0x93, 0x42,
        0xC5, 1, 0xf0,   //F5 E8   ///1
        0xC0, 2, 0x12, 0x12,
        0xC1, 1, 0x03,
        0x2A, 4, 0x00, 0x00, 0x01, 0x3f,
        0x2B, 4, 0x00, 0x00, 0x00, 0xef,
        0xb0, 1, 0xe0,
        0xf6, 3, 0x00, 0x01, 0x01,
        0xb6, 4, 0x0a, 0xe0, 0x1d, 0x04,
        
        0xC2, 1, 0xA3,
        0xB4, 1, 0x02,

        0xE0,15,0x00,0x0C,0x11,0x04,0x11,0x08,0x37,0x89,0x4C,0x06,0x0C,0x0A,0x2E,0x34,0x0F,
        0xE1,15,0x00,0x0B,0x11,0x05,0x13,0x09,0x33,0x67,0x48,0x07,0x0E,0x0B,0x2E,0x33,0x0F,

        ///0xB6, 2, 0x0A, 0x40,  ///2
        0x11, TFT_CMD_DELAY, 6,
        0x29, TFT_CMD_DELAY, 1,
        0x36, 1, 0x08,
    };

    commandList(ILI9342_init);
}
*/

{
  writecommand(0xC8);
  writedata(0xFF);
  writedata(0x93);
  writedata(0x42);

  writecommand(ILI9341_PWCTR1);
  writedata(0x12);
  writedata(0x12);

  writecommand(ILI9341_PWCTR2);
  writedata(0x03);

  writecommand(0xB0);
  writedata(0xE0);

  writecommand(0xF6);
  writedata(0x00);
  writedata(0x01);
  writedata(0x01);

  writecommand(ILI9341_MADCTL);    // Memory Access Control
#ifdef M5STACK
  writedata(TFT_MAD_MY | TFT_MAD_MV | TFT_MAD_COLOR_ORDER); // Rotation 0 (portrait mode)
#else
  writedata(TFT_MAD_MX | TFT_MAD_COLOR_ORDER); // Rotation 0 (portrait mode)
#endif

  writecommand(ILI9341_PIXFMT);
  writedata(0x55);

  writecommand(ILI9341_DFUNCTR);    // Display Function Control
  writedata(0x08);
  writedata(0x82);
  writedata(0x27);

  writecommand(ILI9341_GMCTRP1);    //Set Gamma
  writedata(0x00);
  writedata(0x0C);
  writedata(0x11);
  writedata(0x04);
  writedata(0x11);
  writedata(0x08);
  writedata(0x37);
  writedata(0x89);
  writedata(0x4C);
  writedata(0x06);
  writedata(0x0C);
  writedata(0x0A);
  writedata(0x2E);
  writedata(0x34);
  writedata(0x0F);

  writecommand(ILI9341_GMCTRN1);    //Set Gamma
  writedata(0x00);
  writedata(0x0B);
  writedata(0x11);
  writedata(0x05);
  writedata(0x13);
  writedata(0x09);
  writedata(0x33);
  writedata(0x67);
  writedata(0x48);
  writedata(0x07);
  writedata(0x0E);
  writedata(0x0B);
  writedata(0x2E);
  writedata(0x33);
  writedata(0x0F);

  writecommand(ILI9341_SLPOUT);    //Exit Sleep

  spi_end();
  delay(120);
  spi_begin();

  writecommand(ILI9341_DISPON);    //Display on

}

/*
{
  writecommand(0xC8);
  writedata(0xFF);
  writedata(0x93);
  writedata(0x42);

  writecommand(ILI9341_PWCTR1);
  writedata(0x12);
  writedata(0x12);

  writecommand(ILI9341_PWCTR2);
  writedata(0x03);

  writecommand(0xB0);
  writedata(0xE0);

  writecommand(0xF6);
  writedata(0x00);
  writedata(0x01);
  writedata(0x01);

  writecommand(ILI9341_MADCTL);    // Memory Access Control
#ifdef M5STACK
  writedata(TFT_MAD_MY | TFT_MAD_MV | TFT_MAD_COLOR_ORDER); // Rotation 0 (portrait mode)
#else
  writedata(TFT_MAD_MX | TFT_MAD_COLOR_ORDER); // Rotation 0 (portrait mode)
#endif

  writecommand(ILI9341_PIXFMT);
  writedata(0x55);

  writecommand(ILI9341_DFUNCTR);    // Display Function Control
  writedata(0x08);
  writedata(0x82);
  writedata(0x27);

  writecommand(ILI9341_GMCTRP1);    //Set Gamma

  writedata(0x00);
  writedata(0x0C);
  writedata(0x11);
  writedata(0x04);
  writedata(0x11);
  writedata(0x08);
  writedata(0x37);
  writedata(0x89);
  writedata(0x4C);
  writedata(0x06);
  writedata(0x0C);
  writedata(0x0A);
  writedata(0x2E);
  writedata(0x34);
  writedata(0x0F);

  writecommand(ILI9341_GMCTRN1);    //Set Gamma
  writedata(0x00);
  writedata(0x0B);
  writedata(0x11);
  writedata(0x05);
  writedata(0x13);
  writedata(0x09);
  writedata(0x33);
  writedata(0x67);
  writedata(0x48);
  writedata(0x07);
  writedata(0x0E);
  writedata(0x0B);
  writedata(0x2E);
  writedata(0x33);
  writedata(0x0F);

  writecommand(ILI9341_SLPOUT);    //Exit Sleep

  spi_end();
  delay(120);
  spi_begin();

  writecommand(ILI9341_DISPON);    //Display on

}
*/