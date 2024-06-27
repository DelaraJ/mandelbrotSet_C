from PIL import Image, ImageDraw

MAX_ITER =80


def mandelbrot(c):
    z=0
    n=0
    while abs(z) <= 2 and n < MAX_ITER:
        z = z*z + c
        n += 1
    return n

## Image size (pixels)
#mikhaym begim tool va arze safhamoon che ghadr bashe
WIDTH = 600
HEIGHT = 400

## Plot window
#inja mikhaym begim ke oon safhe 600 dar 400 ro az koja ta kojaye safhe mokhtasat bekeshe
#yani masalan az -2 ta 1 ro ke baze x hast ba 600 ghesmat taghsim mikonim
#real part = x & imaginary part = y
RE_START = -2
RE_END = 1
IM_START = -1
IM_END = 1

#ketabkhoone image baraye pillow hast ke mitoonim bahash aks dorost konim
im = Image.new('HSV' , (WIDTH, HEIGHT), (0, 0, 0))
draw = ImageDraw.Draw(im)
#khob alan darim migim ye aksi hast be name im ke to ino 
#bede be Draw chon ma mikhaym toosh chizi bekeshim
#HSV? ye noe rang bandie (mesle RGB ke ye noe digast)


#alan vazehe ke bayad for too dar too bezanim ke har 
#pixelo meghdaresho hesab bokone

for x in range (0, WIDTH):
    for y in range (0, HEIGHT):
        ##convert pixel coordinate to complex number
        c = complex (RE_START + (x / WIDTH) * (RE_END - RE_START),
                     IM_START + (y / HEIGHT) * (IM_END - IM_START))
        ##compute the number of iterations
        #c = -0.54 + 0.54i
        m = mandelbrot(c)
        ##the color depends on the number of iterations
        hue = int (255 * m / MAX_ITER) 
        saturation = 255
        value =255 if m < MAX_ITER else 0
        ##plot the point
        if (hue<86) :
            draw.point([x, y], (hue+170, saturation, value))
        else    :
            draw.point([x, y], (hue-86, saturation, value))
        

im.convert('RGB').save('first.png', 'PNG')

#as you know to run this you should use python mandelbrot.py command:)
# use command copy output.png output_1.png

#baraye bishtar kardan teyfe rangi bayad MAX_ITER ro ziad konim
#baraye resolution bayad WIDTH va HEIGHT ro ziad konim