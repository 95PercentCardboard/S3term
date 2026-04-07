#include <Arduino_GFX_Library.h>
#include <math.h>
#include "gfx.h"
#include "pins.h"
#include "objtypes.h"
#include "model.h"


//lets other processes kill it
TaskHandle_t cubeTaskHandle = NULL;

//project 3d vertexCount to 2d
void flatten(points3d* in, points2d* out,int count, float fov) {
	for (int i = 0; i < count; i++) {
		float depth = in[i].z + fov; //add fov to the z value so it looks 3d
		out[i].x = in[i].x / depth;
		out[i].y = in[i].y / depth; //make points closer to the center the farther back they are
	}
}

//rotate function
points3d rotate(points3d p, float angleX, float angleY, float angleZ) {
	points3d r;

	//X axis
	r.x = p.x;
	r.y = p.y * cos(angleX) - p.z * sin(angleX);
	r.z = p.y * sin(angleX) + p.z * cos(angleX);

	//Y axis
	float	rx = r.x * cos(angleY) + r.z * sin(angleY);
	float	rz = -r.x * sin(angleY) + r.z * cos(angleY);
	r.x = rx;
	r.z = rz;

	//Z axis
	float zx = r.x * cos(angleZ) - r.y * sin(angleZ);
  float zy = r.x * sin(angleZ) + r.y * cos(angleZ);
  r.x = zx;
  r.y = zy;

	return r;
}

//main function that is called
void cubeTask(void* pvParameters){
	

	//some vairables to tweak things
	int screenW = 320;
	int screenH = 240;

	float scale = screenW * zoom;
	float offsetX = screenW / float(2.0);
	float offsetY = screenH / float(2.0);

	//float fov = float(2.0); this is defined in the model file now
	
	//initialize these two so they're not trapped in the function
	float angleY = float(0.0);
	float angleX = float(0.0);
	float angleZ = float(0.0);

	while (true) {

		//Serial.printf("stack remaining: %d\n\r", uxTaskGetStackHighWaterMark(NULL));

		//create 2d points
		struct points3d rotated[vertexCount];
		struct points2d flats[vertexCount];
 		
		for (int i = 0; i < vertexCount; i++) {
			rotated[i] = rotate(verts[i], angleX, angleY, angleZ);
		}

		flatten(rotated, flats, vertexCount, fov); //take 3d points as input and output the projected points to the 2d struct
		
		//for (int i = 0; i < vertexCount; i++) {
 	  //    Serial.printf("flats[%d]: (%.3f, %.3f)\n\r", i, flats[i].x, flats[i].y);
		//}
			
		int boxW = 124;
		int boxH = 124;

		gfx->fillRect((screenW-boxW)/2,(screenH-boxH)/2,boxW,boxH,BLACK);
		
		for (int i = 0; i < edgeCount; i++) {
	    int ax = (int)(flats[edges[i].a].x * scale + offsetX);
	    int ay = (int)(flats[edges[i].a].y * scale + offsetY);
	    int bx = (int)(flats[edges[i].b].x * scale + offsetX);
	    int by = (int)(flats[edges[i].b].y * scale + offsetY);
			
			gfx->drawLine(ax, ay, bx, by, GREEN);
		}
	
		angleX += float(rX);
		angleY += float(rY);
		angleZ += float(rZ);

		vTaskDelay(pdMS_TO_TICKS(1000/fps)); //about 60fps
	}
}

void CUBE() {
	xTaskCreatePinnedToCore(
		cubeTask,
		"cubeTask",
		memUsage,
		NULL,
		1,
		&cubeTaskHandle,
		0
		);
}

void CUBE_STOP() {
	if (cubeTaskHandle != NULL) {
		vTaskDelete(cubeTaskHandle);
		cubeTaskHandle = NULL;
	}
}
