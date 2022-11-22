from PIL import Image, ImageDraw, ImageFont



img = Image.new('RGB', (956, 956), color = 'white')
d = ImageDraw.Draw(img)

x1 = x2 = -1
y1 = 0
y2 = 955
for i in range(10):
    if i % 3 == 0:
        x1 += 4
        x2 += 4
        d.line([(x1, y1), (x2, y2)], fill = 'black', width = 8)
        x1 += 4
        x2 += 4
    else:
        x1 += 2
        x2 += 2
        d.line([(x1, y1), (x2, y2)], fill = 'black', width = 4)
        x1 += 2
        x2 += 2
    x1 += 100
    x2 += 100

x1 = 0
x2 = 955
y2 = y1 = -1
for i in range(10):
    if i % 3 == 0:
        y1 += 4
        y2 += 4
        d.line([(x1, y1), (x2, y2)], fill = 'black', width = 8)
        y1 += 4
        y2 += 4
    else:
        y1 += 2
        y2 += 2
        d.line([(x1, y1), (x2, y2)], fill = 'black', width = 4)
        y1 += 2
        y2 += 2
    y1 += 100
    y2 += 100

img.save("blank_grid.png")






for i in range(10):
    # create image of color 'color' and of size (99, 97)
    img = Image.new('RGB', (100, 100), color = 'white')

    # loads the font to use on text
    fnt = ImageFont.truetype('/usr/share/fonts/TTF/Roboto-Regular.ttf', 80)

    # draw on the image
    d = ImageDraw.Draw(img)
    d.text((50, 50), str(i), font = fnt, anchor = 'mm', fill = 'black')

    img.save("num_" + str(i) + ".png")
