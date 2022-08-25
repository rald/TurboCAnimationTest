#define GRAPHICS_IMPLEMENTATION
#include "graphics.h"

#define CANVAS_IMPLEMENTATION
#include "canvas.h"

dword pal[]={
	0x001A1C2CL,
	0x005D275DL,
	0x00B13E53L,
	0x00EF7D57L,
	0x00FFCD75L,
	0x00A7F070L,
	0x0038B764L,
	0x00257179L,
	0x0029366FL,
	0x003B5DC9L,
	0x0041A676L,
	0x0073EFF7L,
	0x00F4F4F4L,
	0x0094B0C2L,
	0x00566C86L,
	0x00333C57L
};


int main() {

	int i,j;

	Canvas *canvas;

	byte *buf=calloc(SCREEN_SIZE,sizeof(byte));

	int f=0;
	int z=4;
	bool g=true;

	word start;

	int a[]={0,1,2,3,2,1};
	int n=6;


	SetMode(0x13);

	for(i=0;i<16;i++) {
		int r=(int)((pal[i] & 0x00FF0000L) >> 16);
		int g=(int)((pal[i] & 0x0000FF00L) >> 8);
		int b=(int)((pal[i] & 0x000000FFL));
		r=(int)((double)r/255*63);
		g=(int)((double)g/255*63);
		b=(int)((double)b/255*63);

		SetPalette(i,r,g,b);
	}

	canvas=Canvas_LoadCVS("sprite.cvs");

	start=*myclock;

	while(!kbhit()) {

		memset(buf,0,SCREEN_SIZE);

		Canvas_Draw(buf,canvas,0,0,a[f],z);

		Canvas_Draw(buf,canvas,SCREEN_WIDTH-canvas->w,SCREEN_HEIGHT-canvas->h,a[f],1);

		if(g) {
			for(i=0;i<=canvas->w;i++) {
				DrawLine(buf,i*z,0,i*z,canvas->h*z,15);
			}

			for(j=0;j<=canvas->h;j++) {
				DrawLine(buf,0,j*z,canvas->w*z,j*z,15);
			}
		}

		for(i=0;i<16;i++) {
			FillRect(buf,(i%8)*16,(i/8)*16+SCREEN_HEIGHT-32,16,16,i);
		}


		vsync();
		memcpy(VGA,buf,SCREEN_SIZE);

		if(*myclock-start>=3) {
			start=*myclock;
			f=(f+1)%n;
		}

	}



	getchar();

	SetMode(0x03);

	return 0;
}
