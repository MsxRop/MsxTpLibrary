
{Unit games.inc – contains all the procedures useful for handling input}
{from input devices: mouse, cursor keys, joystick with Turbo Pascal 3.01}
{to be included for using joystick and cursors in Turbo Pascal programs for MSX}


{Functions & procedures about games control}
{Function PAD(Func:byte):integer;}
{procedure getMousecoord(port:byte; var X:integer;var Y:integer);}
{function MousePresent(port:byte): boolean;}
{Function Stick(port:byte):byte;}
{Function Strig(KeyToTest:byte):boolean;}


const
jmov : joyval =
(0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1);


{Calls the BIOS routine GTPAD, which handles input from pad, lightpen, and mouse according to the value of Func}
{if Func = 12 it handles the mouse connected to port 1, if Func = 16 it handles the mouse connected to port 2}

Function PAD(Func:byte):integer;
BEGIN
RegA:=Func;
MSxBIOS(GTPAD);
Pad:=RegA;
END;



{Returns the X and Y offsets according to the movement of the mouse connected to the specified port}
procedure getMousecoord(port:byte; var X:integer;var Y:integer);
BEGIN
    case port of
    
    1:
        begin
            X:=Pad(13);
            Y:=Pad(14);
        end;

    2:
        begin
     
            X:=Pad(17);
            Y:=Pad(18);
        end;
    end;
END;


{Returns true if the mouse is connected to the specified port}
function MousePresent(port:byte): boolean;
var cc,x1,y1,x2,y2:byte;
BEGIN
    case port of
    1:
        begin
            cc := pad(12);      {updates packet}
            x1 := Pad(13);
            y1 := Pad(14);
            delay(10);            {small delay}
            cc := Pad(12);      {updates again}
            x2 := Pad(13);
            y2 := Pad(14);
        end;

    2:
        begin
            cc := pad(16);      {updates packet}
            x1 := Pad(17);
            y1 := Pad(18);
            delay(10);            {small delay}
            cc := Pad(16);      {updates again}
            x2 := Pad(17);
            y2 := Pad(18);
        end;
    end;

MousePresent := (x1 <> x2) or (y1 <> y2);
END;

{Gets the state of the directional keys (port 0) or the position of the Joystick (port 1 or 2)}

Function Stick(port:byte):byte;

BEGIN
    RegA:=port;
    MsxBios(GTSTCK);
    Stick:=RegA;
END;
{Gets the state of the space bar or the buttons of the Joystick or mouse – true if pressed}
{KeyToTest = 0 space bar – 1..3 A/B buttons of joystick or mouse 1 – 2..4 A/B buttons of joystick or mouse 2}

Function Strig(KeyToTest:byte):boolean;

BEGIN
    RegA:=KeyToTest;
    MsxBios(GTTRIG);
    Strig:=(RegA<>0);
END;

