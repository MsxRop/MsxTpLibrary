
{Unit Sprites.inc – contains all the procedures useful for defining and}
{managing sprites in the MSX1 and MSX2 environment with Turbo Pascal 3.01}
{to be included for using sprites in Turbo Pascal programs for MSX}

{--------------------------------------------------------------------------------------------}
                                    {Format routines}
{--------------------------------------------------------------------------------------------}

{Returns TRUE if sprites are enlarged. By checking bit 1 of VDP register #1}
function SpriteCurrentMag: boolean;
var
  big: byte;
BEGIN
  big := VDP1;  {read VDP register #1 }
  if (big and $01) = 0 then
    SpriteCurrentMag := false     {bit1 = 0 → sprite normale}
  else
    SpriteCurrentMag := true;     {bit1 = 1 → sprite doppio}
END;


{Returns false if sprite is 8×8 and true if sprite is 16×16. By checking bit 0 of VDP register #1}
function SpriteCurrentSize: boolean;
var
  big: byte;
BEGIN
  big := VDP1;  {read VDP register #1 }
  if (big and $02) = 0 then
    SpriteCurrentSize := false     {bit0 = 0 → sprite 8x8}
  else
    SpriteCurrentSize := true;     {bit0 = 1 → sprite 16x16}
END;



{--------------------------------------------------------------------------------------------}
                    {Videoram address routines for sprite handling}
{--------------------------------------------------------------------------------------------}

{Returns the base address of the sprite pattern table}
function GetSpritePattern(numero_modello:byte): integer;
var 
    Big:boolean;
    mult:byte;
    Addr:integer;
BEGIN
    Big:=SpriteCurrentSize;
    if (big= true) then mult:=32;
    if (big= false) then mult:=8;
    Addr:=numero_Modello*mult;
    GetSpritepattern := PATBAS+Addr;
END;


{Returns the base address of the sprite attribute table}
function GetSpriteAttrib(numero_modello:byte): integer;
var
    mult:byte;
    Addr:integer;
BEGIN
    mult:=4;
    Addr:=numero_Modello*mult;
    GetSpriteAttrib := ATRBAS+Addr;
END;


{Returns the base address of the sprite color table – MSX2 only}
function GetSpriteColorTabel(numero_modello:byte): integer;
BEGIN
    GetSpriteColorTabel:=(GetSpriteAttrib(numero_modello)-$200);
END;


{--------------------------------------------------------------------------------------------}
                    {Sprite size and enlargement control routines}
{--------------------------------------------------------------------------------------------}

{Sets the sprite size and enlargement}
Procedure SetSpriteDim(size16, zoom2x: boolean);
var
  old, new: byte;
BEGIN
  old := VDP1;                          {Gets the value of VDP register 1}
  new := old and $FC;                   {Clears only bits 0 and 1 by masking with B11111100}
  if size16 then 
    new := new or $02;                  {if requested, sets the size bit to 1}
  if zoom2x then 
    new := new or $01;                  {if requested, sets the enlargement bit to 1}
  Writevdp(1,new)                       {Writes the new value into VDP register 1}
END;



{--------------------------------------------------------------------------------------------}
                      {Sprite shape and color definition routines}
{--------------------------------------------------------------------------------------------}

{inserts into the pattern table the sprite model indicated by numero_modello}
{0..63 if sprite is 16×16, 0..255 if sprite is 8×8}
procedure DefSprite(numero_modello: byte; spriteData: spritedata);
var
  i, basePattern, indirizzo_forma, lim: integer;
  is16: boolean;
BEGIN
  is16 := SpriteCurrentSize;     {true = 16x16, false = 8x8}

  if is16 then
  begin
    lim := 31;                   {32 byte = 4 pattern of 8 byte}
    basePattern := numero_modello * 4;   {4 pattern blocks}
  end
  else
  begin
    lim := 7;                    {8 byte = 1 pattern}
    basePattern := numero_modello;
  end;

  {each pattern occupies 8 bytes}
  indirizzo_forma := PATBAS + (basePattern * 8);

  for i := 0 to lim do
    VPOKE(indirizzo_forma + i, spriteData[i]);
END;


{inserts into the color table the values for type‑2 sprites}
procedure SetSpriteColor(piano_sprite: byte; spcolor: spritecolor);
var
  i, baseSprite, indirizzo_colore: integer;
BEGIN
  baseSprite := piano_sprite;            
  indirizzo_colore := ATRBAS - $200 + (baseSprite * 16);
  for i := 0 to 15 do
    VPOKE(indirizzo_colore + i, spcolor[i]);
END;


{--------------------------------------------------------------------------------------------}
                  {Sprite display, color, and collision control routines}
{--------------------------------------------------------------------------------------------}

{Displays on screen the sprite numero_modello on Piano_Sprite – 0..31}
procedure PutSprite(Piano_Sprite, x, y, numero_modello, ec: byte);
var
  indirizzo, pattern: integer;
  is16: boolean;
BEGIN
  is16 := SpriteCurrentSize;

  if is16 then
    pattern := numero_modello * 4      { blocco da 4 pattern }
  else
    pattern := numero_modello;

  indirizzo := GetSpriteAttrib(Piano_Sprite);

  VPOKE(indirizzo,     y);             { byte 0: Y }
  VPOKE(indirizzo + 1, x);             { byte 1: X }
  VPOKE(indirizzo + 2, pattern);       { byte 2: pattern }
  VPOKE(indirizzo + 3, ec);            { byte 3: EC / colore:
                                         - MSX1: use color
                                         - MSX2: use Sprite Color Table }
END;


{returns true if two sprites are colliding}
{does not check visible pixels but uses sprite size and the X,Y coordinates of the two sprites}
{Software sprite collision position based}
function SpriteCollision(spritea,spriteb:Byte):boolean;
var 
  i,indirizzoa,indirizzob,dim,modo:integer;
  x1,y1,x2,y2:integer;
  
BEGIN
  SpriteCollision:=false;                                       {upon entering the routine, Collision is considered false}

  if SpriteCurrentSize=True then 
      dim :=16;                                   
  
  if SpriteCurrentSize=false then 
      dim :=8;
  
  if SpriteCurrentmag=true then 
    dim :=dim *2;
  
  indirizzoa:=(GetSpriteAttrib(spritea));
  indirizzob:=(GetSpriteAttrib(spriteb));
  y1:=vpeek(indirizzoa);                          {take Y of first sprite}
  x1:=vpeek(indirizzoa+1);                        {take X of first sprite}
  y2:=vpeek(indirizzob);                          {take Y of second sprite}
  x2:=vpeek(indirizzob+1);                        {take X of second sprite}
  if (abs(x1-x2)<dim) and (abs(y1-y2)<dim) then   
      SpriteCollision:=true;                                    {return true if sprites dimensions are overlapped} 
 
    
END;
 
{returns the coordinates of the point where a collision occurred}
{hardware sprite collision}
{ this procedure is called after a colission detected by vdp satus register. onli msx2+ e turbo r}
procedure HSpriteCollision(var X,Y:Integer);
var 
  r3,r4,r5,r6:byte;
  
BEGIN

  r3:=ReadVdpStateReg(3);                                     
  r4:=ReadVdpStateReg(4);
  r5:=ReadVdpStateReg(5);
  r6:=ReadVdpStateReg(6);

{calculates the coordinates where the collision occurred}
  X:= (r3 and r4) - 12;
  Y:= (r5 and r6) - 8  ;                                        
  
END;

{Returns true if a collision occurs between sprite's pixels that are not transparent}
function IsSpriteCollision:boolean;
var 
  r0:byte;
BEGIN
  r0 := ReadVdpStateReg(0);   { resetta i flag }
  IsSpriteCollision := (r0 and $20) <> 0;
END;
