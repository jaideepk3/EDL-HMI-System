#ifndef UI_H
#define UI_H
#include <stdint.h>

#define GPU_TARGET_FPS (30)
#define GPU_X 320
#define GPU_Y 240
#define GPU_MIN ( GPU_X/2 < GPU_Y ? GPU_X : GPU_Y )
#define GPU_BORDER_X ( GPU_X/2 > GPU_Y ? (GPU_X/2-GPU_Y)/2 : 0 )
#define GPU_BORDER_Y ( GPU_X/2 < GPU_Y ? (GPU_Y-GPU_X/2)/2 : 0 )
#define GPU_REST ( GPU_X/2-2*GPU_BORDER_X )
#define S1_CENTER_X ( GPU_X/4 )
#define S1_CENTER_Y ( GPU_Y/2 )
#define S2_CENTER_X ( 3*GPU_X/4 )
#define S2_CENTER_Y ( GPU_Y/2 )
#define TEXTURE_SIZE 64
#define B_WIDTH 8
#define TOP_MARGIN 25
typedef struct {
    const uint16_t * fontArray;
    const uint8_t width;
    const uint8_t height;
} FontDescription;

#define GPU_Color uint16_t


extern const FontDescription fontDescription[4];

extern uint16_t _framebuffer[GPU_X*GPU_Y];
//convert to rgb565
#define RGB(r, g, b) ( (uint16_t)((r)&0xf8 ) | (((uint16_t)((b)&0x00f8))<<5) | (((g)&0x00e0)>>5) | (((uint16_t)((g)&0x001c))<<6) )
#define WHITE RGB(255,255,255)
#define ORANGE RGB(255, 95, 0)
#define BLACK RGB(0,0,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(217,207,39)
#define CYAN (0,100,100)
#define BROWN (150,75,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define C_GRAY_LIGHT RGB(192,192,192)
#define C_GRAY_MEDIUM RGB(128,128,128)
#define C_GRAY_DARK RGB(64,64,64)
#define C_C1 RGB(39,153,216)
#define C_C2 RGB(216,39,153)
#define C_C3 RGB(153,216,39)
#define LAVENDER RGB(226,209,249)
#define LIGHT_BLUE RGB(173,216,230)
#define PEACH RGB(252, 237, 218)
#define PURPLE RGB(128,0,128)
#define LIME RGB(243, 217, 12)
#define FLUORESCENT_ORANGE RGB(245, 118, 10)
#define SKYBLUE RGB(10, 137, 245)
extern GPU_Color BG_COLOR ;
void GPU_Init();
void cross_sign();
void GPU_ClearFramebuffers();
void GPU_Render();
void LeftHalfFilledCircle(GPU_Color color, int16_t x, int16_t y, int16_t radius);
void RightHalfFilledCircle(GPU_Color color, int16_t x, int16_t y, int16_t radius);
void DrawSmoothBar(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height);
void GPU_DrawPixel(GPU_Color color, uint16_t x, uint16_t y);
void GPU_DrawLine(GPU_Color color, int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void GPU_DrawLetter(GPU_Color color, const FontDescription * fontDescription, int16_t x, int16_t y, char letter);
void GPU_DrawText(GPU_Color color, const FontDescription * fontDescription, int16_t x, int16_t y, const char * text, uint16_t len);
 void GPU_DrawEmptyRectangle(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height);
void GPU_DrawFilledRectangle(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height);
void GPU_DrawFilledCircle(GPU_Color color, int16_t x, int16_t y, int16_t radius);
//x,y = midpoint of one side VERTICAL TRIANGLE
void DrawFilledTriangle(GPU_Color color, int16_t x, int16_t y, int16_t side,int16_t height,char* direction);
//x,y draw rectangle upwards from x,y instead of down
void DrawVerticalRectangle(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height);
void display_png();
uint32_t getMinutes();
#endif