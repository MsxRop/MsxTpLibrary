
{Unit Msx.inc – contains all the variables, constants, and types}
{required for programming in the MSX2 environment with Turbo Pascal 3.01}
{must be included first in Turbo Pascal programs for MSX}
Const
{---------------------------------------------}
              {Rom BIOS entry}
{---------------------------------------------}
CHGMOD=$5F;     {selects the operating mode of the VDP main-rom}
CHGMDP=$01B5 ;  {sets the screen mode sub rom}
CLS=$C3;        {clears the screen  main-rom}
GRPPRG=$8D;     {prints a character on the graphic screen mIN-rom}
GRPPRT=$89;     {prints a character on the graphic screen sub-rom}
GTSTCK=$D5;     {returns the state of the selected joystick main-rom}
GTTRIG=$D8;     {returns the state of the selected fire button main-rom}
GTPAD=$DB;      {touch, trackball or mouse main-rom}
GTPDL=$DE;      {paddle main-rom}
NEWPAD=$01AD;   {PAD for MSX2 sub-rom}
LDIRVM=$59;     {copies data from VRAM to RAM main-rom}
LDIRMV=$5C;     {copies data from RAM to VRAM main-rom}
MAPXYC=$111;    {map coordinates for the physical address main-rom}
SCALXY=$10E;    {ensures that a point generated in the registers remains on screen main-rom}
SETC=$120;      {sets the current pixel with the specified attributes main-rom}
READC=$011D;    {reads the color of a pixel main-rom}
WRTPSG=$93;     {writes a byte to the PSG register main-rom}
ENASCR=$44;     {enables the screen main-rom}
WRTVRM=$4D;     {writes a byte to VRAM – A = data, HL = VRAM address main-rom}
WRTVRM2=$0109;  {writes a byte to VRAM – A = data, HL = VRAM address SUB ROM}
RDVRM=$4A;      {reads a byte from VRAM – A = data, HL = VRAM address main-rom}
RDVR2=$010D;    {reads a byte from VRAM – A = data, HL = VRAM address SUB ROM}
DISSCR=$41;     {disables the screen main-rom}
WRTSPR= $00D0;  {writes sprite data}
WRTVDP=$47;     {writes a byte to the VDP register main-rom}
RDVDP=$13E;     {reads the VDP status register  main-rom}
VDPSTA=$0131;   {reads status registers 0..9 → MSX2 – sub rom}
CHGCLR=$0062;   {sets FOREGROUND, BACKGROUND, BORDER colors main rom}
CHGCLR2=$111;   {sets FOREGROUND, BACKGROUND, BORDER colors SUB rom}
CLRSPR=$69;     {initializes sprites, input $FCAF (SCREEN MODE) CHGCLR2=$111 main rom}
FILVRM=$56;     {fills an area of VRAM with a byte main rom}
BIGFIL=$016B;   {fills an area of VRAM with a byte sub rom}
LIDRAW=$593C;   {draws a line main rom}
DOGRAPH=$0085;  {draws a line sub rom}
BLINE=$5912;    {draws a box (MSX2 compatible) main rom?}
NVBXLN=$00C9;   {draws a rectangle sub rom}
NVBXFL=$00CC;   {draws a filled rectangle sub rom}
CALSLT=$001C;   {calls a routine in any slot main rom}
POSIT=$00C6;    {positions the cursor at coordinates X,Y main rom}
BEP=$00C0;      {like BEEP in BASIC main rom}
SETPAG=$013D;   {sets the display page and the active VRAM page sub rom}
BLTVV=$0191;    {Copy data from vram to vram}     
BLTVM=$0195;    {copy data from main ram to vram}
BLTMV=$0199;    {copy data from vram to main ram}
BLTVD=$019D;    {copy from disk to VRAM sub rom}
BLTDV=$01A1;    {c0py data from vram to disk}
BLTMD=$01A5;    {copy data from disk to main ram}
BLTDM=$01A9;    {copy data from main ram to disk}
NWRVRM=$0177;   {writes a byte to VRAM – A = data, HL = VRAM address main rom}
CHGSND=$0135;   {1 bit sound generator -  main rom}
CHSNS=$009C;    {Read keyboard buffer - main rom}
FNKSTR= $F87F;  {Function key string}
{---------------------------------------------}
        {Vdp Copy hi speed commands }
{---------------------------------------------}

   HMMC = $F0 ; {High speed Byte Cpu  -> Vram }
   YMMM = $E0 ; {High speed Byte Vram -> Vram in y-axis }
   HMMM = $D0 ; {High speed Byte Vram -> Vram in x- and y-axis }
   HMMV = $C0 ; {High speed Byte Vdp  -> Vram = paint a box }

   LMMC = $B0 ; {Logical Dot     Cpu  -> Vram }
   LMCM = $A0 ; {Logical Dot     Vram -> Cpu  }
   LMMM = $90 ; {Logical Dot     Vram -> Vram }
   LMMV = $80 ; {Logical Dot     Vdp  -> Vram = paint a box }

{---------------------------------------------}
    {Copy directions for the ARG-register }
{---------------------------------------------}

   Copy_Right = 0;
   Copy_Down  = 0;
   Copy_Left  = 4;
   Copy_Up    = 8;
   ExpansionVram   = 32 ;
   Vram  = 0 ;

  
{---------------------------------------------}
          {VDP status registers}
{---------------------------------------------}
  Svdp0 = 0;          {Interrupt information}
  Svdp1 = 1;          {Interrupt information}
  Svdp2 = 2;          {Information and control register}
  Svdp3 = 3;          {Detected horizontal coordinate (low)}
  Svdp4 = 4;          {Detected horizontal coordinate (high)}
  Svdp5 = 5;          {Vertical coordinate detected (low)}
  Svdp6 = 6;          {Vertical coordinate detected (high)}
  Svdp7 = 7;          {Data obtained by some VDP command}
  Svdp8 = 8;          {Horizontal coordinate obtained by some search command (low)}
  Svdp9 = 9;          {Vertical coordinate obtained by some search command (low)}


{---------------------------------------------}
{Data types used by the routines}
{---------------------------------------------}

Type
Str6=string[6];                     {6‑character string returned by the Str function}
str2=string[2];                     {music note. ex: 'C+' or 'f-'}
Str255 = string[255];               {Generic String}
str4=string[4];                     {4‑character string returned by the Hex function}
str32=string[32];                   {string length for the WriteG procedure}
str12=string[12];                   {filename string in MSX‑DOS format xxxxxxxx.yyy}   
str16=string[16];                   {Lenght of key string}             
TSmallBuf = array[0..4096] of byte; {buffer for reading an image file}
spritedata=array[0..31] of byte;    {Data of sprite definition}
spritecolor=array[0..15] of byte;   {Sprite color in mode 2 sprite}
TScreenParams = record              {Structure for screen instruction}
Mode: byte;                         {screen mode, mandatory}
Width: byte;                        {optional, text mode only}
end;
joyval = array[1..16] of integer;   {direction of the 8 joystick o cursor keys input}

{---------------------------------------------}
{Global variables}
{---------------------------------------------}

Var

{CPU registers}
RegA,RegF:byte;                 {Z80 8‑bit registers}

regBC,regDE,regHL,              {Z80 16‑bit registers}
regIX,regIY: INTEGER;

{System variables}
MSXTYPE:byte absolute $002D;    {MSX type (0=MSX1, 1=MSX2, 2=MSX2+, 3=TurboR)}
MAINROM:byte absolute $FCC1;    {Main-ROM slot}
SUBROM:byte absolute $FAF8;     {Sub-ROM slot (0 for MSX1)}
ATRBYT:byte absolute $F3F2;     {current color in graphic modes}
BAKCLR:byte absolute $F3EA;     {background color}
BDRCLR:byte absolute $F3EB;     {border color}
FORCLR:byte absolute $F3E9;     {foreground color}
NAMBAS:integer absolute $F922;  {address of the name table according to the selected graphic mode}
PATBAS:integer absolute $F926;  {address of sprite patterns according to the selected graphic mode}
ATRBAS:integer absolute $F928;  {address of sprite attributes according to the selected graphic mode}
LOGOPR:byte absolute $FB02;     {logical operator in graphics}
GRPACX:byte absolute  $FCB7;    {x coordinate}
GRPACY:byte absolute  $FCB9;    {y coordinate}
GXPOS: byte absolute  $FCB3;    {x position of the graphic cursor}
GYPOS: byte absolute  $FCB5;    {y position of the graphic cursor}
KEYPR: byte absolute  $f336;    {FF if a key is pressed, $03 if Ctrl+Stop, 0 otherwise}
KEYVL: byte absolute  $f337;    {ASCII code of the pressed key}
KLIKSW:byte absolute  $f3db;    {keyclick: 1 on, 0 off}
CSRY:  byte absolute  $f3dc;    {cursor y coordinate in text mode}
CSRX:  byte absolute  $f3dd;    {cursor x coordinate in text mode}
KEYONF:byte absolute  $f3de;    {shows (1) or hides (2) the function keys}
LINL40: byte absolute $F3AE;    {Screen 0 width}
LINL32: byte absolute $F3AF;    {Screen 1 width}
SCRMOD :Byte absolute $FCAF;    {returns the current screen mode}
CLOC : Byte absolute  $F92A;    {x 2}
CMASK: Byte absolute  $F92C;    {x 1}
ACPAGE:bYTE ABSOLUTE  $FAF6;    {Active page in MSX >1 graphic's mode}
Vdp0 : Byte absolute  $F3DF;    {VDP register 0}
Vdp1 : Byte Absolute  $f3e0;    {VDP register 1}
Vdp2 : Byte Absolute  $f3e1;    {VDP register 2}
Vdp3 : Byte Absolute  $f3e2;    {VDP register 3}
Vdp4 : Byte Absolute  $f3e3;    {VDP register 4}
Vdp5 : Byte Absolute  $f3e4;    {VDP register 5}
Vdp6 : Byte Absolute  $f3e5;    {VDP register 6}
Vdp7 : Byte absolute  $f3e6;    {VDP register 7}
Vdp8 : Byte Absolute  $ffe7;    {VDP register 8}
Vdp9 : Byte Absolute  $ffe8;    {VDP register 9}
Vdp10: Byte Absolute  $ffe9;    {VDP register 10}
Vdp11: Byte Absolute  $ffea;    {VDP register 11}
Vdp12: Byte Absolute  $ffeB;    {VDP register 12}
Vdp13: Byte Absolute  $ffeC;    {VDP register 13}
Vdp14: Byte Absolute  $ffeD;    {VDP register 14}
Vdp15: Byte Absolute  $ffeE;    {VDP register 15}
Vdp16: Byte Absolute  $ffeF;    {VDP register 16}
Vdp17: Byte Absolute  $ffF0;    {VDP register 17}
Vdp18: Byte Absolute  $ffF1;    {VDP register 18}
Vdp19: Byte Absolute  $ffF2;    {VDP register 19}
Vdp20: Byte Absolute  $ffF3;    {VDP register 20}
Vdp21: Byte Absolute  $ffF4;    {VDP register 21}
Vdp22: Byte Absolute  $fFF5;    {VDP register 22}
Vdp23: Byte Absolute  $ffF6;    {VDP register 23}
Vdp25: Byte Absolute  $ffFA;    {VDP register 25}
Vdp26: Byte Absolute  $ffFB;    {VDP register 26}
Vdp27: Byte Absolute  $ffFC;    {VDP register 27}
ClickSW: integer absolute $F3DB;{controls keyboard click}
SpriteColorTable,               {base address of the sprite color table}
SpriteAttributeTable,           {base address of the sprite attribute table}
SpritePatternTable:integer;     {base address of the sprite pattern table}


{Command array for the VDP access}

_sx  :Integer Absolute $f562 ;
_sy  :Integer Absolute $f564 ;
_dx  :Integer Absolute $f566 ;
_dy  :Integer Absolute $f568 ;
_nx  :Integer Absolute $f56a ;
_ny  :Integer Absolute $f56c ;
_col :Byte Absolute    $f56e ;
_arg :Byte Absolute    $f56f ;
_cmd :Byte Absolute    $f570 ;

{System timer}
Jiffy: integer absolute $FC9E;  {1/50" timer}

{Screen mode record}
ScrInit: TscreenParams;
{---------------------------------------------}
{Routine calls}
{---------------------------------------------}

{Calls BIOS routines from the MAIN ROM}
Procedure MsxBios(VIX: integer);
BEGIN
Inline(

$F3/                    { DI – disables interrupts }
$CD/*+19/               { CALL (PC+19) – jumps to the specified BIOS routine }
$FB/                    { EI – re‑enables interrupts }
$32/RegA/               { LD (RegA),A     – saves A }
$22/RegHL/              { LD (RegHL),HL   – saves HL }
$ED/$43/RegBC/          { LD (RegBC),BC   – saves BC }
$ED/$53/RegDE/          { LD (RegDE),DE   – saves DE }
$18/$1B/                { JR +1Bh – jumps to the final part of the routine }
$DD/$2A/VIX/            { LD IX,(VIX)     – loads IX with the BIOS routine address }
$3A/RegA/               { LD A,(RegA)     – loads A }
$2A/RegHL/              { LD HL,(RegHL)   – loads HL }
$ED/$4B/RegBC/          { LD BC,(RegBC)   – loads BC }
$ED/$5B/RegDE/          { LD DE,(RegDE)   – loads DE }
$08/                    { EX AF,AF' – swaps AF ↔ AF' (CALSLT uses AF') }
$DB/$A8/                { IN A,(A8h) – reads the current primary slot }
$F5/                    { PUSH AF – saves the slot on the stack }
$E6/$F0/                { AND F0h – isolates the slot number (upper 2 bits) }
$C3/$8C/$F3             { JP F38Ch – jumps to CALSLT in the MAIN ROM }
);
END;

{Calls BIOS routines from the SUB‑ROM}
Procedure Msx2Bios(VIX: integer);
BEGIN
Inline(
$F5/              { PUSH AF }
$C5/              { PUSH BC }
$D5/              { PUSH DE }
$E5/              { PUSH HL }
$DD/$E5/          { PUSH IX }
$FD/$E5/          { PUSH IY }
$3A/RegA/         { LD A,(RegA) }
$ED/$4B/RegBC/    { LD BC,(RegBC) }
$ED/$5B/RegDE/    { LD DE,(RegDE) }
$2A/RegHL/        { LD HL,(RegHL) }
$DD/$2A/VIX/      { LD IX,(entry) }
$FD/$2A/$F7/$FA/  { LD IY,(FAF7h) = SLTWRK }
$CD/$1C/$00/      { CALL CALSLT }
$32/RegA/         { LD (RegA),A }
$ED/$43/RegBC/    { LD (RegBC),BC }
$ED/$53/RegDE/    { LD (RegDE),DE }
$22/RegHL/        { LD (RegHL),HL }
$DD/$22/RegIX/    { LD (RegIX),IX }
$FD/$22/RegIY/    { LD (RegIY),IY }
$FD/$E1/          { POP IY }
$DD/$E1/          { POP IX }
$E1/              { POP HL }
$D1/              { POP DE }
$C1/              { POP BC }
$F1               { POP AF }
);
END;
