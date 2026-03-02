#include "OLED_INTERFACE.h"
#include <util/delay.h>
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "../../MCAL/SPI/SPI_INTERFACE.h"  // ????? ??? ????? SPI functions

/* ST7789 Command set (only used commands) */
#define CMD_SWRESET    0x01
#define CMD_SLPOUT     0x11
#define CMD_COLMOD     0x3A
#define CMD_MADCTL     0x36
#define CMD_CASET      0x2A
#define CMD_RASET      0x2B
#define CMD_RAMWR      0x2C
#define CMD_INVON      0x21
#define CMD_NORON      0x13
#define CMD_DISPON     0x29
#define CMD_RAMCTRL    0xB0
#define CMD_VSCRDEF    0x33
#define CMD_PORCTRL    0xB2
#define CMD_GCTRL      0xB7
#define CMD_VCOMS      0xBB
#define CMD_LCMCTRL    0xC0
#define CMD_VDVVRHEN   0xC2
#define CMD_VRHS       0xC3
#define CMD_VDVSET     0xC4
#define CMD_FRCTRL2    0xC6
#define CMD_PWCTRL1    0xD0
#define CMD_PVGAMCTRL  0xE0
#define CMD_NVGAMCTRL  0xE1

/* helper macros to control pins */
static inline void DC_Command(void){ DIO_VoidSetPinValue(ST7789_PORT, ST7789_PIN_DC, LOW); }
static inline void DC_Data(void){ DIO_VoidSetPinValue(ST7789_PORT, ST7789_PIN_DC, HIGH); }
static inline void CS_Select(void){ DIO_VoidSetPinValue(ST7789_PORT, ST7789_PIN_CS, LOW); }
static inline void CS_Unselect(void){ DIO_VoidSetPinValue(ST7789_PORT, ST7789_PIN_CS, HIGH); }
static inline void RST_Off(void){ DIO_VoidSetPinValue(ST7789_PORT, ST7789_PIN_RST, HIGH); }
static inline void RST_On(void){ DIO_VoidSetPinValue(ST7789_PORT, ST7789_PIN_RST, LOW); }

/* Low level send functions using your SPI driver */
static void st_send_cmd(u8 cmd)
{
    DC_Command();
    CS_Select();
    SPI_u8TransmitData(cmd);
    CS_Unselect();
}

static void st_send_data(u8 data)
{
    DC_Data();
    CS_Select();
    SPI_u8TransmitData(data);
    CS_Unselect();
}

/* Send multiple data bytes (faster: keep CS low while sending stream) */
static void st_send_data_stream(const u8 *buff, u16 len)
{
    DC_Data();
    CS_Select();
    for(u16 i=0; i<len; i++){
        SPI_u8TransmitData(buff[i]);
    }
    CS_Unselect();
}

/* Set memory window (column & row range) */
static void st_set_window(u16 x0, u16 y0, u16 x1, u16 y1)
{
    u8 data[4];

    // column address (CASET)
    st_send_cmd(CMD_CASET);
    data[0] = (u8)((x0 >> 8) & 0xFF);
    data[1] = (u8)(x0 & 0xFF);
    data[2] = (u8)((x1 >> 8) & 0xFF);
    data[3] = (u8)(x1 & 0xFF);
    st_send_data_stream(data,4);

    // row address (RASET)
    st_send_cmd(CMD_RASET);
    data[0] = (u8)((y0 >> 8) & 0xFF);
    data[1] = (u8)(y0 & 0xFF);
    data[2] = (u8)((y1 >> 8) & 0xFF);
    data[3] = (u8)(y1 & 0xFF);
    st_send_data_stream(data,4);

    // write to RAM
    st_send_cmd(CMD_RAMWR);
}

/* Initialize pins & SPI then init sequence */
void ST7789_Init(void)
{
    /* Configure control pins as outputs */
    DIO_VoidSetPinDirection(ST7789_PORT, ST7789_PIN_DC, OUTPUT);
    DIO_VoidSetPinDirection(ST7789_PORT, ST7789_PIN_RST, OUTPUT);
    DIO_VoidSetPinDirection(ST7789_PORT, ST7789_PIN_CS, OUTPUT);

    /* default states */
    CS_Unselect();
    DC_Data();
    RST_Off();

    /* init SPI master (your function) */
    SPI_VoidInitMaster();

    /* Hardware reset */
    RST_On(); _delay_ms(10);
    RST_Off(); _delay_ms(120);

    /* Software reset */
    st_send_cmd(CMD_SWRESET);
    _delay_ms(150);

    /* Sleep out */
    st_send_cmd(CMD_SLPOUT);
    _delay_ms(120);

    /* Color mode 16-bit/pixel (RGB565) */
    st_send_cmd(CMD_COLMOD);
    st_send_data(0x55); // 16-bit/pixel (0x55 = 16-bit)
    _delay_ms(10);

    /* Memory data access control (rotation) */
    st_send_cmd(CMD_MADCTL);
    st_send_data(0x00); // default: adjust later with ST7789_SetRotation
    _delay_ms(10);

    /* Other optional: porch, VCOM, power ... reasonable defaults */
    st_send_cmd(CMD_PORCTRL);
    st_send_data(0x0C);
    st_send_data(0x0C);
    st_send_data(0x00);
    st_send_data(0x33);
    st_send_data(0x33);

    st_send_cmd(CMD_GCTRL);
    st_send_data(0x35);

    st_send_cmd(CMD_VCOMS);
    st_send_data(0x19);

    st_send_cmd(CMD_LCMCTRL);
    st_send_data(0x2C);

    st_send_cmd(CMD_VDVVRHEN);
    st_send_data(0x01);

    st_send_cmd(CMD_VRHS);
    st_send_data(0x12);

    st_send_cmd(CMD_VDVSET);
    st_send_data(0x20);

    st_send_cmd(CMD_FRCTRL2);
    st_send_data(0x0F);

    st_send_cmd(CMD_PWCTRL1);
    st_send_data(0xA4);
    st_send_data(0xA1);

    st_send_cmd(CMD_PVGAMCTRL);
    // gamma positive (default values)
    u8 pg[14] = {0xD0,0x04,0x0D,0x11,0x13,0x2B,0x3F,0x54,0x4C,0x18,0x0D,0x0B,0x1F,0x23};
    st_send_data_stream(pg,14);

    st_send_cmd(CMD_NVGAMCTRL);
    u8 ng[14] = {0xD0,0x04,0x0C,0x11,0x13,0x2C,0x3F,0x44,0x51,0x2F,0x1F,0x1F,0x20,0x23};
    st_send_data_stream(ng,14);

    /* Normal display on */
    st_send_cmd(CMD_NORON);
    _delay_ms(10);

    st_send_cmd(CMD_DISPON);
    _delay_ms(120);

    /* finally set full window (optional) */
    st_set_window(0,0,ST7789_WIDTH-1,ST7789_HEIGHT-1);
}

/* Fill entire screen with a color (color is RGB565 16-bit) */
void ST7789_FillScreen(u16 color)
{
    u16 total = ST7789_WIDTH * ST7789_HEIGHT;
    u8 hi = (u8)(color >> 8);
    u8 lo = (u8)(color & 0xFF);

    st_set_window(0,0,ST7789_WIDTH-1,ST7789_HEIGHT-1);

    DC_Data();
    CS_Select();
    for(u32 i=0; i<total; i++){
        SPI_u8TransmitData(hi);
        SPI_u8TransmitData(lo);
    }
    CS_Unselect();
}

/* Draw single pixel */
void ST7789_DrawPixel(u16 x, u16 y, u16 color)
{
    if(x>=ST7789_WIDTH || y>=ST7789_HEIGHT) return;
    st_set_window(x,y,x,y);
    u8 hi = (u8)(color >> 8);
    u8 lo = (u8)(color & 0xFF);
    st_send_data(hi);
    st_send_data(lo);
}

/* Fill rectangle */
void ST7789_FillRect(u16 x, u16 y, u16 w, u16 h, u16 color)
{
    if(x>=ST7789_WIDTH || y>=ST7789_HEIGHT) return;
    u16 x2 = (x + w - 1);
    u16 y2 = (y + h - 1);
    if(x2 >= ST7789_WIDTH) x2 = ST7789_WIDTH - 1;
    if(y2 >= ST7789_HEIGHT) y2 = ST7789_HEIGHT - 1;

    u32 total = (u32)(x2 - x + 1) * (u32)(y2 - y + 1);
    u8 hi = (u8)(color >> 8);
    u8 lo = (u8)(color & 0xFF);

    st_set_window(x,y,x2,y2);
    DC_Data();
    CS_Select();
    for(u32 i=0; i<total; i++){
        SPI_u8TransmitData(hi);
        SPI_u8TransmitData(lo);
    }
    CS_Unselect();
}

/* Draw image (RGB565 array) */
void ST7789_DrawImage(u16 x, u16 y, u16 w, u16 h, const u16 *img)
{
    if(x>=ST7789_WIDTH || y>=ST7789_HEIGHT) return;
    u16 x2 = x + w - 1;
    u16 y2 = y + h - 1;
    if(x2 >= ST7789_WIDTH) x2 = ST7789_WIDTH - 1;
    if(y2 >= ST7789_HEIGHT) y2 = ST7789_HEIGHT - 1;

    st_set_window(x,y,x2,y2);

    DC_Data();
    CS_Select();
    u32 pixels = (u32)w * (u32)h;
    for(u32 i=0; i<pixels; i++){
        u16 c = img[i];
        SPI_u8TransmitData((u8)(c>>8));
        SPI_u8TransmitData((u8)(c & 0xFF));
    }
    CS_Unselect();
}

/* Set rotation (0..3). Implementation uses MADCTL values for ST7789 */
void ST7789_SetRotation(u8 m)
{
    u8 mad = 0;
    switch(m & 3) {
        case 0: mad = 0x00; break; // normal
        case 1: mad = 0x60; break; // rotate 90
        case 2: mad = 0xC0; break; // rotate 180
        case 3: mad = 0xA0; break; // rotate 270
    }
    st_send_cmd(CMD_MADCTL);
    st_send_data(mad);
}

