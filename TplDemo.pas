program tpldemo;
{$i Msx.inc}
{$i GENERIC.inc}
{$i VRAM.INC}
{$i VDP.inc}
{$i Sprites.inc}
{$i Games.inc}


const
    MyData : spritedata =
     (0,0,1,3,3,7,7,4,15,15,15,15,14,4,0,0,96,240,
    176,184,184,188,124,30,126,254,158,6,2,0,0,0);

var 
  
    a,o,v,od,vd   :integer;
    MouseOk       :boolean;




BEGIN

    Scrinit.mode:=8;                            {as SCREEN2 in BASIC}                      
    Screen(Scrinit);                            {set the screen mode}     
    color(15,1,1);
    clearscreen;
    circle(128,106,40,8);                       {some example of graphics primitives}
    lines(0,0,100,100,15,0,0);
    drawbox(0,0,20,20,15,0,0);
    fillbox(10,10,20,20,15,0,0);
    pset(128,106,12,0,0);
    writeg(1,1,str(point(128,106,0)),15,0);     {Write on graphic screen}
    o:=100;
    v:=100;
    SetSpriteDim(true, false);                  {Sprite dimension: 1x1, 16x16 pixels}
    DefSprite(0,Mydata);                        {Define sprite 0 with Mydata}
  
        MouseOK:=MousePresent(1);               {Check if mouse is present}
        repeat
        if MouseOK then                         {so if mouse is present, get the mouse coordinates and move the sprite}
            begin
                a := Pad(12);                   {Required to update delta X and delta Y}
                GetmouseCoord(1,od,vd);
                o := o +(lo(od));               { delta X }
                v := v +(lo(vd));               { delta Y }
                putsprite(0,o,v,0,8);           {put sprite 0 at (o,v) on page 0}
            end; 
    
    until strig(1);                             {until left mouse button is pressed}
    scrinit.mode:=0;                            
    Scrinit.width:=80;
    screen(scrinit);

END .
