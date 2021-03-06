//////////////////////////////////////////////////////////////////////////////////
// [ Net_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
// Net
//
// [::Last modi: 16.08.17 L.ey (µ~)::]
//
//
#ifndef _C_NET_H_
 #define _C_NET_H_
 
   #include <iostream>
   #include <fstream>
   #include <string>
   #include <sstream>
   #include <iomanip>
   
   #include <errno.h>
   
   using namespace std;
 
   #include <sigc++/sigc++.h>
   
   #include <glibmm/dispatcher.h>
   
   #include "Net_Protokoll_Header.hpp"
   
   #include "C_Net_Interface.hpp"
   #include "C_Net_Raw.hpp"
   #include "C_Net_Raw_Arp.hpp"
   
   typedef unsigned char  UCHAR;
   typedef unsigned short WORD;
   typedef unsigned int   DWORD;
 
//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
   const int C_NET_ERROR = 0x00;
   const int C_NET_READY = 0x01;
   
   const int C_NET_BUFFER = 0x1400;
   const int C_NET_ID_ARP = 0xFFAA;
   
//////////////////////////////////////////////////////////////////////////////////
// STRUCT
//////////////////////////////////////////////////////////////////////////////////

   
//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////
   
   class C_Net {
     
      public:
	
         C_Net(){};
        ~C_Net(){};

         int start();
         int send(const S_Net_Interface* pSInterface, S_ArpPacket* pSArp, int cPackets, int cSleep);

         ///////////////////////////////////////////////////////////////
       
         C_Net_Interface  CNInterface;

         array<unsigned char, C_NET_BUFFER> CA_Arp;
         
         C_Net_Raw_Arp CNArp;
         C_Net_Raw     CNRaw;

         /////////////////////////////////////////
         // Signal
         void on_arp_data(int id, int cData);
         
      private: 

         int status;
   };
 
#endif // _C_NET_H_
