// ToolsManagedManager.cpp
//

#include "precompiled.h"

#include "radiant/QERTYPES.H"
#include "radiant/editorEntity.h"
#include "radiant/EditorMap.h"

// jmarshall
#include "tools_managed.h"
#include "../renderer/Image.h"
// jmarshall end

using namespace ToolsManaged;
extern bool g_editorAlive;

IToolsManaged *toolsManaged;


TOOLS_EXPORTFUNC(cmdSystem, BufferCommandText, (const char *str), (CMD_EXEC_NOW, str) )
TOOLS_EXPORTFUNC_RET(fileSystem, OSPathToRelativePath, (const char *str), ( str) )
TOOLS_EXPORTFUNC_RET(fileSystem, RelativePathToOSPath, (const char *str), ( str) )
TOOLS_EXPORTFUNC_RET(fileSystem, OpenFileRead, (const char *relativePath, bool allowCopyFiles, const char* gamedir), ( relativePath, allowCopyFiles, gamedir ) )
TOOLS_EXPORTFUNC_RET(fileSystem, OpenFileWrite, (const char *relativePath,  const char* gamedir), ( relativePath,  gamedir ) )
TOOLS_EXPORTFUNC(fileSystem, CloseFile, (idFile *file), ( file ) )
TOOLS_EXPORTFUNC_RET(declManager, FindType, (declType_t type, const char *name, bool makeDefault), ( type, name, makeDefault ) )

// IdDict
TOOLS_EXPORTFUNC_NOOBJ( idDict, Set, (idDict *obj, const char *str, const char *str1), (str, str1) )
TOOLS_EXPORTFUNC_NOOBJ_RET( idDict, GetString, (idDict *obj, const char *key), (key) )
TOOLS_EXPORTFUNC_NOOBJ_RETTYPE( idDict, idVec3, GetVector, (idDict *obj, const char *key), (key) )
TOOLS_EXPORTFUNC_NOOBJ_RETTYPE( idDict, int, GetNumKeyVals, (idDict *obj), () )
TOOLS_EXPORTFUNC_NOOBJ_RETTYPE( idDict, idKeyValueInstance, GetKeyValInstance, (idDict *obj, int index), (index) )

extern "C" __declspec(dllexport) byte *TOOLAPI_Editor_GetDiffuseImageForMaterial( const char *mtr, int &width, int &height )
{
	const idMaterial *mat = declManager->FindMaterial( mtr );

	idImage *editorImage = mat->GetEditorImage();

	width = editorImage->uploadWidth;
	height = editorImage->uploadHeight;

	return editorImage->ReadDriverPixels( 0, 0 );
}

extern "C" __declspec(dllexport) int TOOLAPI_Editor_GetNumMaterials( void )
{
	return declManager->GetNumDecls( DECL_MATERIAL );
}

extern "C" __declspec(dllexport) const char *TOOLAPI_Editor_GetMaterialNameByIndex( int indx )
{
	const idMaterial *material = declManager->MaterialByIndex( indx, false );

	return material->GetName();
}

extern "C" __declspec(dllexport) const char *TOOLAPI_Editor_GetMapName( void )
{
	static idStr s;
	
	s = &currentmap[0];

	
	return s.StripFileExtension().c_str();
}


extern "C" __declspec(dllexport) idDict *TOOLAPI_Entity_GetTemplate( const char *type )
{
	idDeclEntityDef *def = (idDeclEntityDef *)declManager->FindType( DECL_ENTITYDEF, type );
	
	assert( def != NULL );

	return &def->dict;
}

extern "C" __declspec(dllexport) idDict *TOOLAPI_Entity_GetEntityDict( const char *name )
{
	entity_t *ent = FindEntity( "name", name );
	if(!ent) {
		return NULL;
	}

	return &ent->epairs;
}


/*
=================
idToolInterfaceLocal::GetValueFromManagedEnum
=================
*/
int idToolInterfaceLocal::GetValueFromManagedEnum(const char * enumTypeStrv, const char * enumValStrv)
{
	long value = 0;


	toolsManaged->GetValueFromManagedEnum( _com_util::ConvertStringToBSTR(enumTypeStrv), _com_util::ConvertStringToBSTR(enumValStrv), &value );
	return value;
}

void Brush_Update();
extern "C" __declspec(dllexport) void TOOLAPI_Brush_Update( void )
{
	Brush_Update();
}

// Export 

/*
==================
idToolInterfaceLocal::InitToolsManaged
==================
*/
void idToolInterfaceLocal::InitToolsManaged( void ) {
	CoCreateInstance( __uuidof(ToolsManagedPrivate), NULL, CLSCTX_INPROC_SERVER, __uuidof(IToolsManaged), (void **)&toolsManaged);
}

/*
==================
idToolInterfaceLocal::ShowDebugConsole
==================
*/
void idToolInterfaceLocal::ShowDebugConsole( void ) {
	toolsManaged->ShowDebugConsole();
}
/*
==================
idToolInterfaceLocal::RadiantPrint
==================
*/
void idToolInterfaceLocal::RadiantPrint( const char *text ) {
	if ( g_editorAlive ) {
		toolsManaged->PrintToConsole( _com_util::ConvertStringToBSTR(text) );
	}

	
}
