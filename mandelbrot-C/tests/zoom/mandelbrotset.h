#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__

#include"defs.h"
#include<math.h>

int MAX_ITER=500;
int get_mbs_iter(double a, double b)
{

    double re_c = a;
    double im_c = b;
    int n = 0;
    while (n < MAX_ITER) {
    double re = a * a - b * b;
    double im = 2.0 * a * b;
    a = re + re_c;
    b = im + im_c;
    n++;
    if (a + b > 7.0) break;
    }
    
    return n;
    

}
void hsv2rgb(int i, int min, int max, COLORINDEX* p)
{
    p->b = i;
    p->g = i;
    p->r = i;
}

double degree2radian (double angle)
{
    double rad=angle*0.0174533;
    return rad;
}

void UpdateImageData(ImageState* state)
{
    for(int x=0; x<state->width; x++)
        
        {   
            //double rad_angle= degree2radian(state->angle);
            double rad_angle;
            for(int y=0; y<state->height; y++)
            {
                
                // rad_angle = to_radian(state->angle);
                rad_angle= (state->angle) *3.14/180;
                double dx= (state->minx) + (double)x/(state->width)*(state->maxx-state->minx); 
                double dy= (state->miny) + (double)y/(state->height)*(state->maxy-state->miny);
                double rx = dx * cos(rad_angle) + dy * sin(rad_angle);
                double ry = -dx * sin(rad_angle) + dy * cos(rad_angle);

                int iter = get_mbs_iter(rx, ry);
                int ch= 180 * iter / MAX_ITER;
                // if (ch==259)            ch-=1;
                // else if (ch%2==1)       ch+=1;
                if (iter> MAX_ITER || iter < 13 )     state->bmFileData.bmData[y * state->width + x]=0;
                else                               state->bmFileData.bmData[y * state->width + x]=1+ch;
                // state->bmFileData.bmData[y * state->width + x] = iter;
       
            }

        }
         color_table(&(state->bmFileData));
        // for( int i=0;i<256;i++)
        // {
        //     int hue = (int) (((double)i / 255)*360);
        //     hsv2rgb(hue,100,100,&(state->bmFileData.bmHeader.colorIdx[i]));
        // }

}

    void ChangeCenter(ImageState* state, double newcx, double newcy, int steps)
    {
        double x = (newcx - state->cx )/steps;
        double y = (newcy - state->cy )/steps;

        for(int i=0;i<steps; i++)
        {
            state->cx  +=  x;
            state->cy  +=  y;
            state->minx += x;
            state->maxx += x;
            state->miny += y;
            state->maxy += y;
            UpdateImageData(state);
            WriteBitmapFile(state->image_count++, & state->bmFileData);
        }
    }
    void ChangeCenterZoom(ImageState* state, double newcx, double newcy,double zoom, int steps)
{
    double x = (newcx - state->cx )/steps;
    double y = (newcy - state->cy )/steps;

    double zoom_step = (1-1/zoom)/steps;
    for(int i=0;i<steps; i++)
    {
        double r = (state->maxx-state->minx) * zoom_step;
        double u = (state->maxy-state->miny) * zoom_step;
        state->cx  +=  x ;
        state->cy  +=  y ;
        state->maxx =state->maxx + x - r ;
        state->minx =state->minx + x + r ;
        state->maxy =state->maxy - u + y ;
        state->miny =state->miny + u + y ;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeZoom(ImageState* state, double zoom, int steps)   
{
    
    double zoom_step = (1-1/zoom)/steps;
    for(int i=0; i<steps; i++)
    {
    double r = (state->maxx-state->minx) * zoom_step;
    double u = (state->maxy-state->miny) * zoom_step;
        state->maxx -=  r ;
        state->minx +=  r ;
        state->maxy -=  u ;
        state->miny +=  u ;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}
void ChangeUnZoom(ImageState* state, double zoom, int steps)   
{
    
    double zoom_step = (zoom-1)/steps;
    double r = (state->maxx-state->minx) * zoom_step;
    double u = (state->maxy-state->miny) * zoom_step;
    for(int i=0; i<steps; i++)
    {
        state->maxx +=  r ;
        state->minx -=  r ;
        state->maxy +=  u ;
        state->miny -=  u ;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeRotation(ImageState* state, double angle, int steps)
{
    double angle_step = angle / steps;
    for(int i=0; i<steps; i++)
    {
        state->angle += angle_step;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void Hold(ImageState* state, int steps)                   
{
    for(int i=0; i<steps; i++)
    {
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeCenterRotate(ImageState* state, double newcx, double newcy,double angle, int steps)
{
        double x = (newcx - state->cx )/steps;
        double y = (newcy - state->cy )/steps;
        double angle_step = angle / steps;

        for(int i=0;i<steps; i++)
        {
            state->cx  +=  x;
            state->cy  +=  y;
            state->minx += x;
            state->maxx += x;
            state->miny += y;
            state->maxy += y;
            state->angle += angle_step;
            UpdateImageData(state);
            WriteBitmapFile(state->image_count++, & state->bmFileData);
        }
}
#endif