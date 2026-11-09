
{Unit VDP.inc – contains all the calls to BIOS routines}
{required for programming in the MSX2 environment with Turbo Pascal 3.01}
{must be included after Msx.inc in Turbo Pascal programs for MSX}


{Select the screen mode and the width of text mode}
{use the structure ScrInit (of type TScreenParams), a record with two field: mode & width}
{In text mode, 0 or 1, the width parameter set the width of the screen}
{In graphic mode, 2 to 12, the width parameter can be omitted and is ignored}
{For example:}
{Scrinit.mode 0;}
{Scrinit.width 80; for msx2 is correct, if used in msx1 don't return any error but fix the width to 40}
{Screen(Scrinit);}

procedure Screen(P: TScreenParams);
var
  mode,wid:byte;
  model:byte;

BEGIN

  model:=peekBIOS($002D);  

  wid:=p.width;
  mode:=p.mode;
  if model=0 then
    begin
      if mode=0 then
        begin
          if (wid<1) then wid:=1;
          if (wid>40) then wid:=40;
          LINL40:=wid;            {width for SCREEN0 - in MSX1}
          regA:=mode;
          MsxBios(CHGMOD);
        end;
        
    end;

  if model >0 then
    begin
      if mode=0 then
        begin
          if (wid<1) then wid:=1;
          if (wid>80) then wid:=80;
          LINL40:=wid;            {width for SCREEN0 - in MSX2}
          regA:=mode;
          MsxBios(CHGMOD);
          BEEP;
        end;

      if mode=1 then
        begin
          if (wid<1) then wid:=1;
          if (wid>32) then wid:=32;
          LINL32:=wid;                {width for SCREEN1}
          regA:=mode;
          MsxBios(CHGMOD);
        end;
      if Mode >1 then
        begin
          regA:=Mode;
          Msx2Bios(CHGMDP);
        end;
    end;

END;



{Draw pixel at X,Y using color}
Procedure Psetx(x,y:integer;color:byte);

BEGIN
  regBC:=x;
  regDE:=y;
  ATRBYT:=color;
  MsxBios(SCALXY);
  MsxBios(MAPXYC);
  MsxBios(SETC);
END;


{Grab the color at X,Y}
function Pointx(x,y:integer):byte;

BEGIN
  regBC:=x;
  regDE:=y;
  MsxBios(SCALXY);
  MsxBios(MAPXYC);
  MsxBios(READC);
  Pointx:=RegA;
END;


{Draw a line from x1,y1 to x2,y2 using color and logical operator LogOp}
procedure Lines(x1, y1, x2, y2: integer; color,logOp: byte);

var mode: byte;
BEGIN
  mode := SCRMOD ;
  if mode <= 4 then
    begin
      regBC := x1;   
      regDE := y1;   
      GXPOS := x2 ;
      GYPOS := y2;
      ATRBYT := color;
      MsxBios(lidraw) ;
    end
  else
    begin
      GRPACX := 1;        
      LOGOPR := LogOp;
      regBC := x1;       
      regDE := y1;         
      GXPOS := x2;        
      GYPOS := y2;
      ATRBYT := color;
      Msx2Bios(DOGRAPH);
    end;
END;


{Draw an empty box from x1,y1 to x2,y2 using color and logical operator LogOp}
procedure DrawBox(x,y,x1,y1:integer;color,LogOp:byte);

BEGIN
  regBC := x;      
  regDE := y;      
  GXPOS := x1;    
  GYPOS := y1;     
  ATRBYT := color;
  LOGOPR := LogOp;     
  Msx2Bios(NVBXLN);
END;



{Draw a box from x1,y1 to x2,y2 filled using color and logical operator LogOp}
procedure FillBoxx(x,y,x1,y1:integer;color,LogOp:byte);

BEGIN
  regBC := x;
  regDE := y;
  GXPOS := x1;
  GYPOS := y1;
  ATRBYT := color;
  LOGOPR := LogOp;
  Msx2Bios(NVBXFL);
END;

procedure Circle(x, y, r: integer; col: byte);
var
  str255: string[255];
BEGIN
  str255:= 'CIRCLE (' + Str(x) + ',' + Str(y) + '),' + Str(r)+',' + Str(col);
  basic(str255);
END;  

{Clear the screen}
Procedure ClearScreen;

BEGIN
MsxBios(CLS);
END;


{write a string (max 32 characters) in graphic mode at X,Y using color and logical operator LogOp}
Procedure WriteG(x,y:integer; Chars:Str255; color, logic:byte);
Var k:    integer;
    mode: byte;

BEGIN

  ATRBYT := color;
  LOGOPR := logic;
  GRPACX := x;
  GRPACY := y;
  mode:=SCRMOD;

  for k := 1 to Length(Chars) do
  begin
    RegA := Ord(Chars[k]);
    IF (mode>1) and (mode<5) then 
    msxbios(GRPPRG);                  {in case of screen 2 to 4}
    if (mode>5) then
    msx2bios(GRPPRT);                 {in case of screen 5 to 12}

  end;
END;



{Set graphic cursor at X,Y}
procedure GoXY(x, y: integer);
BEGIN
  RegHL:= X+(Y*256);     
  MsxBios(POSIT);
END;



{Set the ForeGround, BackGround  and Border colors}
Procedure Color (ForeGround,BackGround,Border:byte);
BEGIN
  FORCLR:=ForeGround;
  BAKCLR:=BackGround;
  BDRCLR:=Border;
  msx2bios(CHGCLR2);
END;


{Redefine the color pattern of one color setting the red green and blue, like COLOR=(COLOR,R,G,B) IN BASIC}
Procedure SetRGB(Color,r,g,b:Byte);
 Var rb,gr,colour :Byte;
 BEGIN
   rb := r*16+b;
   gr := g;
   Colour := color;
   Inline (
           $F3/$3A/colour /$D3/$99/$3E/$10/$F6/$80/$D3/$99/$3A/ rb /
           $D3/$9A/$3A/ gr /$D3/$9A/$FB
          );
 END;



{Disables the screen presntation}
Procedure HideScreen;
BEGIN
  inline($FD/$2A/$C1/$FC/$DD/$21/$41/$00/$CD/$1C/$00);
END;
{Enables the screen presntation}
Procedure ShowScreen;
BEGIN
  inline ($fd/$2a/$c1/$fc/$dd/$21/$44/$00/$cd/$1c/$00);
END;

{Load a file created with BSAVE"NOMEFILE",S in BAsic}
procedure BLoadS(Filename : str12);
var
  F               : file;
  Hdr             : array[0..6] of byte;
  Buf             : TSmallBuf;
  Readed          : integer;
  LenLo, LenHi    : integer;
  DestLo, DestHi  : integer;
  VRAM            : integer;
  RemLo, RemHi    : integer;
  ToRead          : integer;
  tmp             : integer;
BEGIN
  Assign(F, Filename);
  Reset(F, 1);
  BlockRead(F, Hdr, 7, Readed);
  LenLo   := Hdr[3];
  LenHi   := Hdr[4];
  DestLo  := Hdr[5];
  DestHi  := Hdr[6];
  RemLo := LenLo;
  RemHi := LenHi;
  VRAM := DestLo + (DestHi shl 8);
  
  SetVramAddr(VRAM);



  while (RemHi <> 0) or (RemLo <> 0) do
  begin
    ToRead := SizeOf(Buf);
    if RemHi = 0 then
      if RemLo < ToRead then
        ToRead := RemLo;
        BlockRead(F, Buf, ToRead, Readed);
        if Readed = 0 then
        begin
          RemLo := 0;
          RemHi := 0;
        end
      else
        begin
          CopyFromRam(Addr(Buf), VRAM, Readed);
          VRAM := VRAM + Readed;
          tmp := RemLo - Readed;
          while tmp < 0 do
          begin
            tmp := tmp + 256;
            RemHi := RemHi - 1;
          end;
          RemLo := tmp;
        end;
  end ;
  Close(F);
END;


{------------------------------------}
{           nuove routines           } 
{------------------------------------}


{copies from CPU to VRAM}
Procedure MoveDotToVram(SourceAddress :Integer;Destination_x,
Destination_y:Integer;DestinationPage:Byte;Number_x,Number_y:Integer;
LogicalOperation,Direction:Byte);

Var 
  Address :Integer;

BEGIN
  Address := SourceAddress+1; {Because the firstbyte is set in CMD array. }
  _cmd:= LMMC + LogicalOperation;
  _dy := DestinationPage * 256 + Destination_y ;
  _arg:= Direction ;
  _dx := Destination_x;
  _nx := Number_x;
  _ny := Number_y;
  _col:= Mem[Address-1];
  Inline ($f3/$DD/$2A/Address/
          $3E/$02/$D3/$99/$3E/$8F/$D3/$99/$DB/$99/$CB/$47/
          $20/$F2/$F3/$3E/$20/$D3/$99/$3E/$11/$F6/$80/$D3/$99/$06/$0F/$0E/
          $9B/$21/$62/$F5/$ED/$B3/$3E/$2C/$F6/$80/$D3/$99/$3E/$11/$F6/$80/
          $D3/$99/$3E/$02/$D3/$99/$3E/$8F/$D3/$99/$DB/$99/$CB/$47/$28/$0D/
          $CB/$7F/$28/$EE/$DD/$7E/$00/$DD/$23/$D3/$9B/$18/$E5/$3E/$00/$D3/
          $99/$3E/$8F/$D3/$99/$DB/$99/$fb);
END ; {Lmmc}



Procedure Riga(X1,Y1,X2,Y2 : Integer;Page,Colore,LogOp : Byte);

Var
  DXA,DYA : Integer;

BEGIN
  DXA := Abs(X2-X1);
  DYA := Abs(Y2-Y1);
  _dx := X1;
  _dy := Page*256 + Y1;
  _arg := 0;
  { DIX }
  if X2 < X1 then
     _arg := _arg or 4;
  { DIY }
  if Y2 < Y1 then
     _arg := _arg or 8;
  { MAJ }
  if DYA >= DXA then
  begin
     _nx := DYA;    { long side }
     _ny := DXA;    { short side }
     _arg := _arg or 1;
  end
  else
  begin
     _nx := DXA;    { long side }
     _ny := DYA;    { short side }
  end;
  _col := Colore;
  _cmd := $70 + LogOp; { LINE }
  Common;

END;

Procedure fillBox(
          X1,Y1,
          X2,Y2 : Integer;
          Page  : Byte;
          Colore: Byte;
          LogOp:  byte);

Var
  TX : Integer;
  TY : Integer;

Begin

  if X1 > X2 then
  begin
    TX := X1;
    X1 := X2;
    X2 := TX;
  end;

  if Y1 > Y2 then
  begin
    TY := Y1;
    Y1 := Y2;
    Y2 := TY;
  end;

  _dx := X1;
  _dy := Page * 256 + Y1;

  _nx := X2 - X1 + 1;
  _ny := Y2 - Y1 + 1;

  _col := Colore;

  _arg := 0;

  _cmd := $C0 + Logop;   { BOX }

  Common;

End;


Procedure Box(
          X1,Y1,
          X2,Y2 : Integer;
          Page  : Byte;
          Colore: Byte;
          LogOp : Byte);

Begin

  Riga(X1,Y1,X2,Y1,Page,Colore,LogOp);
  Riga(X2,Y1,X2,Y2,Page,Colore,LogOp);
  Riga(X2,Y2,X1,Y2,Page,Colore,LogOp);
  Riga(X1,Y2,X1,Y1,Page,Colore,LogOp);

End;


Procedure Pset(
          X1,Y1 : Integer;
          Page  : Byte;
          Colore: Byte;
          LogOp : byte);


Begin
  _dx := X1;
  _dy := Page * 256 + Y1;


  _col := Colore;

  _arg := 0;

  _cmd := $50 + Logop;   { PSET }

  Common;

End;


Function Point(
          X1,Y1 : Integer;
          page  : byte): byte;


Begin
  _sx := X1;
  _sy := Page * 256 + Y1;

  _arg := 0;

  _cmd := $40;   { POINT }

  Common;

  Point:=ReadVdpStateReg(7);;
End;

Procedure SCopy(X1,Y1,X2,Y2 : Integer;SrcPage : Byte;DestX,DestY : Integer;DestPage,LogOp : Byte);

BEGIN
  _sx := X1;
  _sy := SrcPage * 256 + Y1;
  _dx := DestX;
  _dy := DestPage * 256 + DestY;
  _nx := X2 - X1 + 1;
  _ny := Y2 - Y1 + 1;
  _arg := 0;
  _cmd:=logOp;
  Msx2Bios(BLTVV);

END;




Procedure CopyToFile(X1,Y1,X2,Y2 : Integer; SrcPage : Byte; NomeFile :  str12);
type 
  nfc =string[15];
var 
  paramstr: nfc;


BEGIN
  paramstr:= '"'+ Nomefile + '"' + #0;  {nome del file da salvare eventualmente completo di indicazione del drive A: o B:}
  _sx := X1;                        {coordinata X iniziale}
  _sy := SrcPage * 256 + Y1;        {coordinata Y iniziale calcolando anche in che pagima si trova}
  _dx :=addr(paramstr)+1;             {Punta al nome del file in formato BASIC quindi coi dopo apici e seguiro da 0}
  _nx := X2 - X1 + 1;               {Calcola la larghezza}
  _ny := Y2 - Y1 + 1;               {}
  RegHL := $F562;

  Msx2Bios(BLTDV);

END;


Procedure CopyFromFile(X,Y: Integer; logOp : Byte; NomeFile :  str12);
type nfc =string[15];
var parstr: nfc;


Begin
parstr:= '"'+ Nomefile + '"' + #0;  {nome del file da salvare eventualmente completo di indicazione del drive A: o B:}
  _sx :=addr(parstr)+1;             {Punta al nome del file in formato BASIC quindi coi dopo apici e seguiro da 0}
  
    _dx :=X ;           {Punta al nome del file in formato BASIC quindi coi dopo apici e seguiro da 0}
  _dy:=Y;
_cmd:=LogOp;

RegHL := $F562;

  Msx2Bios(BLTVD);

End;

