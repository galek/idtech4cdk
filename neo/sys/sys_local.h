/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 GPL Source Code (?Doom 3 Source Code?).  

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#ifndef __SYS_LOCAL__
#define __SYS_LOCAL__

/*
==============================================================

	idSysLocal

==============================================================
*/

class idSysLocal : public idSys {
public:
	virtual void			DebugPrintf( const char *fmt, ... )id_attribute((format(printf,2,3)));
	virtual void			DebugVPrintf( const char *fmt, va_list arg );

	virtual double			GetClockTicks( void );
	virtual double			ClockTicksPerSecond( void );
	virtual cpuid_t			GetProcessorId( void );
	virtual const char *	GetProcessorString( void );
	virtual const char *	FPU_GetState( void );
	virtual bool			FPU_StackIsEmpty( void );
	virtual void			FPU_SetFTZ( bool enable );
	virtual void			FPU_SetDAZ( bool enable );

	virtual void			FPU_EnableExceptions( int exceptions );

	virtual void			GetCallStack( address_t *callStack, const int callStackSize );
	virtual const char *	GetCallStackStr( const address_t *callStack, const int callStackSize );
	virtual const char *	GetCallStackCurStr( int depth );
	virtual void			ShutdownSymbols( void );

	virtual bool			LockMemory( void *ptr, int bytes );
	virtual bool			UnlockMemory( void *ptr, int bytes );

	virtual ID_SYS_HANDLE	DLL_Load( const char *dllName );
	virtual void *			DLL_GetProcAddress( ID_SYS_HANDLE dllHandle, const char *procName );
	virtual void			DLL_Unload( ID_SYS_HANDLE dllHandle );
	virtual void			DLL_GetFileName( const char *baseName, char *dllName, int maxLength );

	virtual sysEvent_t		GenerateMouseButtonEvent( int button, bool down );
	virtual sysEvent_t		GenerateMouseMoveEvent( int deltax, int deltay );

	virtual void			OpenURL( const char *url, bool quit );
	virtual void			StartProcess( const char *exeName, const char *cmdLine, bool quit );
// jmarshall
#ifndef TYPEINFO
	virtual int				Milliseconds( void ) { return Sys_Milliseconds(); }
	virtual void			GrabMouseCursor( bool grab ) { Sys_GrabMouseCursor( grab ); }
	virtual long			FileTimeStamp(struct _iobuf *io) { return Sys_FileTimeStamp( io ); };
	virtual const unsigned char *GetScanTable( void ) { return Sys_GetScanTable(); }
	virtual bool			IsDebuggerPresent( void );

	virtual void			HandleCrashEvent( void );
	virtual void			ForceGameWindowForeground( void );
	virtual idPort			*AllocPort( void ) { return new idPort(); }
	virtual bool			CompareNetAdrBase( const netadr_t a, const netadr_t b ) { return Sys_CompareNetAdrBase(a, b); }
	virtual bool			StringToNetAdr( const char *s, netadr_t *a, bool doDNSResolve ) { return Sys_StringToNetAdr( s, a, doDNSResolve ); }
#else
	virtual int				Milliseconds( void ) { return -1; }
	virtual void			GrabMouseCursor( bool grab ) {  }
	virtual long			FileTimeStamp(struct _iobuf *io) { return -1; };
	virtual const unsigned char *GetScanTable( void ) { return (const unsigned char*)""; }
	virtual bool			IsDebuggerPresent( void ) { return false; }
	virtual void			HandleCrashEvent( void ) {};
	virtual void			ForceGameWindowForeground( void ) { }
	virtual idPort			*AllocPort( void ) { return NULL; }
	virtual bool			CompareNetAdrBase( const netadr_t a, const netadr_t b ) { return false; }
	virtual bool			StringToNetAdr( const char *s, netadr_t *a, bool doDNSResolve ) { return false; }
#endif
	void Sys_DumpCallStack( void );

// jmarshall end
};

#endif /* !__SYS_LOCAL__ */
