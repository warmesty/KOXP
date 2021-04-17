//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Fonksiyonlar.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
	   Form1->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(!Baglan(Edit1->Text) == false){
		ShowMessage("Baðlantý Kuruldu");
	}else
	{
	    ShowMessage("Baðlantý Kurulamadý");
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
	  if(CheckBox2->Checked == true)
	  {
	  WriteLong(ReadLong(KO_CHR)+ KO_WH,0);
	  }
	  else
	  {
	  WriteLong(ReadLong(KO_CHR)+ KO_WH,1);
	  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	 BYTE town[] = {0x48,0x00};
	 SendPackets(town,sizeof(town));	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
     if(CheckBox2->Checked == true)
	  {
	  WriteLong(ReadLong(KO_CHR)+ KO_WH,0);
	  }
	  else
	  {
	  WriteLong(ReadLong(KO_CHR)+ KO_WH,1);
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
	  if(CheckBox4->Checked == true)
	  {
	  WriteLong(ReadLong(KO_CHR)+ KO_PERI,1);
	  }
	  else
	  {
	  WriteLong(ReadLong(KO_CHR)+ KO_PERI,0);
	  }
}
//---------------------------------------------------------------------------

