
{Unit VRAM.INC – contains the calls to BIOS routines}
{for managing VRAM in the MSX environment with Turbo Pascal 3.01}
{must be included after MSX.INC in Turbo Pascal programs}

function ReadVdpStateReg(RegNum:integer):byte;

begin
  RegA:=RegNum;
  MSx2Bios(VDPSTA);
  ReadVdpStateReg:=RegA;
end;


{Fills VRAM with the specified value starting at the given address for the specified number of bytes}
procedure FillVRAM(address, count: integer; value: byte);
BEGIN
  regHL:=address;  
  regBC:=count;  
  regA:=value;   
  Msx2Bios(BIGFIL);
END;


{Copies from RAM to VRAM a quantity len of bytes}
procedure CopyFromRam(sorg,dest,len:integer);

BEGIN
  regHL:=sorg;  
  regDE:=dest;  
  regBC:=len;   
  MsxBios(LDIRMV);
END;

{Copies from VRAM to RAM a quantity len of bytes}
procedure copyFromVram(sorg,dest,len:integer);

BEGIN
  regHL:=sorg;  
  regDE:=dest;  
  regBC:=len;   
  MsxBios(LDIRVM);
END;

{Writes a byte to the VRAM address indicated as Vpoke in BASIC}
PROCEDURE Vpoke(address:integer; valore:byte);

BEGIN
  regA := valore;
  regHL:=address;
  Msx2bios(WRTVRM2);
END;

{Reads a byte from the VRAM address indicated as Vpeek in BASIC}
function Vpeek(address:integer):byte;

BEGIN
  regHL:=address;
  Msx2bios(RDVR2);
  Vpeek:=regA;
END;


{Writes a value into the VDP register}
Procedure WriteVDP(reg, value: byte);
BEGIN
  RegBC:=(value*256)+reg;
  MsxBios(WRTVDP);
END; 

{Selects the display page and the active VRAM page}
Procedure SetPage(DisplayPage,ActivePage:Byte);

Var   
  DPPAGE :Byte Absolute  $FAF5;
  ACPAGE :Byte Absolute  $FAF6;

BEGIN
  DpPage := DispLayPage;
  AcPage := ActivePage;

  Inline (
             $f3
            /$fd/$2a/$f7/$fa    { LD IY,(EXbrsa - 1 }
            /$DD/$21/$3d/$01    { LD IX,setpage }
            /$CD/$1c/00         { CALL CALSLT }
            /$fb
          );
END;

{service routine for setting the VRAM address, used when reading an image file}
procedure SetVramAddr(adr: integer);
begin
  port[$99] := adr and $FF;                  { A0–A7 }
  port[$99] := ((adr shr 8) and $3F) or $40; { A8–A13 + write flag }
end;


