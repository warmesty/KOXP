#define CopyBytes(Dest,Src) memcpy(Dest, (BYTE*)&Src, sizeof(Src))
DWORD KO_PID = 0;
HANDLE KO_HANDLE = 0;
DWORD KO_CHR = 0xE543C0;
DWORD KO_OFF_GOLD = 0xB6C;
DWORD KO_WH = 0x6C0;
DWORD KO_OFF_HP = 0x6BC;
DWORD KO_PKT = 0xE3AC44;
DWORD KO_PKT1 = KO_PKT + 0xC5;
DWORD KO_PERI = 0x57A370;
DWORD KO_SND_FNC = 0x497310;




BOOL Baglan(String windowname)
{
	char *title = windowname.c_str();
	HWND a = FindWindowA(NULL,title);
	if(!a==0){
		GetWindowThreadProcessId(a,&KO_PID);
		ShowMessage(IntToStr((int)KO_PID));
		if(!KO_PID == 0){
			KO_HANDLE = OpenProcess(PROCESS_ALL_ACCESS,false,KO_PID);
		if(!KO_HANDLE == 0){
			return true;
		}else{return false;}
		}else{return false;}
		}else{return false;}

}


DWORD ReadLong(DWORD value)
{
	ReadProcessMemory(KO_HANDLE,(void*)value,&value,sizeof(value),0);
	return value;
}




DWORD ReadFloat(DWORD value)
{
	float rvalue = 0;
	ReadProcessMemory(KO_HANDLE,(void*)value,&rvalue,4,0);
	return value;

}



BYTE ReadByte(DWORD value)
{
	  BYTE rvalue = 0;
	  ReadProcessMemory(KO_HANDLE, (void*)value,&rvalue,1,0);
	  return rvalue;
}


char* ReadString(DWORD value)
{
	  char *buff;
	  buff = (char *) malloc (100);
	  ReadProcessMemory(KO_HANDLE, (void*)value, (LPVOID)buff,100,0);
	  return buff;
}




void WriteLong(DWORD Addr,DWORD Offset)
{
   WriteProcessMemory(KO_HANDLE, (void *)Addr,&Offset,4,0);
}

void WriteByte(DWORD Addr,BYTE Offset)
{
   WriteProcessMemory(KO_HANDLE, (void *)Addr,&Offset,1,0);
}


void WriteFloat(DWORD Addr,float Offset)
{
   WriteProcessMemory(KO_HANDLE, (void *)Addr,&Offset,4,0);
}


//int FindSNDFNC()
//{
//	return ReadByte(KO_SNDX) ^ 0x16;
//}




void ExecuteRemoteCode(BYTE* packets,size_t psize)
{
	LPVOID MemoryAddr = VirtualAllocEx(KO_HANDLE, 0, psize, MEM_COMMIT, PAGE_READWRITE);
    if(!MemoryAddr == 0) {
	  WriteProcessMemory(KO_HANDLE, (LPVOID)MemoryAddr,packets,psize,0);
	  HANDLE hThread = CreateRemoteThread(KO_HANDLE,0,0,(LPTHREAD_START_ROUTINE)MemoryAddr,0,0,0);
	  WaitForSingleObject(hThread,INFINITE);
	  CloseHandle(hThread);
	  }
	  VirtualFreeEx(KO_HANDLE, MemoryAddr, 0, MEM_RELEASE);
}

void SendPackets(BYTE* packets,size_t psize)
{
	LPVOID MemoryAddr = VirtualAllocEx(KO_HANDLE, 0, psize, MEM_COMMIT, PAGE_READWRITE);
	if(!MemoryAddr == 0) {
	   WriteProcessMemory(KO_HANDLE, (LPVOID)MemoryAddr,packets,psize,0);
	   //int Index = FindSNDFNC();
	   //DWORD KO_SND_FNC = ReadLong(ReadLong(KO_PKT) + Index * 4 + 0x40064);

	   BYTE packet[]=
	   {
		   0x60,
		   0x8B,0x0D,0,0,0,0,
		   0x68,0,0,0,0,
		   0xBF,0,0,0,0,
		   0xFF,0xD7,
		   0xC6,0x05,0,0,0,0,0x00,
		   0x61,
		   0xC3,
	   };

	   DWORD addr = (DWORD)MemoryAddr;
	   CopyBytes(packet + 3,KO_PKT);
	   CopyBytes(packet + 8,psize);
	   CopyBytes(packet + 13,addr);
	   CopyBytes(packet + 18,KO_SND_FNC);
	   CopyBytes(packet + 26,KO_PKT1);
	   ExecuteRemoteCode(packet,sizeof(packet));
	   VirtualFreeEx(KO_HANDLE, MemoryAddr,0,MEM_RELEASE);
	}
}


WORD CharHP(){
	 return ReadLong(ReadLong(KO_CHR) + KO_OFF_HP);
}


