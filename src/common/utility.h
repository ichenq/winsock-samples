﻿/**
 *  @file   utility.h
 *  @author ichenq@gmail.com
 *  @date   Oct 19, 2011
 *  @brief  common utilities
 */

#pragma once


#include "config.h"
#include <vector>



enum { BUFE_SIZE = 8192 };


enum OperType
{
    OperClose,
    OperConnect, 
    OperAccept, 
    OperSend, 
    OperRecv, 
    OperDisconnect,
};


struct PER_HANDLE_DATA 
{
    WSAOVERLAPPED   overlap_;
    SOCKET          socket_;
    WSABUF          wsbuf_;
    char            buffer_[BUFE_SIZE];
    OperType        opertype_;
};


template <typename T>
_tstring    ToString(const T& obj)
{
    _tstringstream strm;
    strm << obj;
    return strm.str();
}



inline HANDLE   CreateCompletionPort(size_t concurrency)
{
    return ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, concurrency);
}


inline bool     AssociateDevice(HANDLE hCompletionPort, HANDLE hDevice, ULONG_PTR completionkey)
{
    assert(hCompletionPort != INVALID_HANDLE_VALUE);
    return (::CreateIoCompletionPort(hDevice, hCompletionPort, completionkey, 0) == hCompletionPort);
}



// converts a sockaddr_in structure into a human-readable string 
_tstring	AddressToString(const sockaddr_in& addr);


// converts a numeric string to a sockaddr_in structure
bool        StringToAddress(const _tstring& straddr, sockaddr_in* paddr);



// format mac address
std::string FormateMAC(const BYTE* pMac, size_t len);


// get mac address and push back to a vector
void    GetMAC(std::vector<std::string>& vec);


