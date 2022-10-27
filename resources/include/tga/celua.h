#ifndef _TGA_CELUA_H
#define _TGA_CELUA_H

#include <stdint.h>

/// Initializes the CELUA DLL.
/// \param name Name of the lua server to connect to.
/// \return boolean indicating success.
extern int CELUA_Initialize(const char* name);

/// Executes lua code on the main CE UI thread.
/// \param luacode The lua code to execute.
/// \param param An integer parameter to the function. Called "parameter" in the lua code's context.
/// \return The return value of the function, if integral. Undefined otherwise.
extern size_t CELUA_ExecuteFunction(const char* luacode, size_t parameter);

/// Executes lua code in the lua server (not waiting for the UI thread).
/// \param luacode The lua code to execute.
/// \param param An integer parameter to the function. Called "parameter" in the lua code's context.
/// \return The return value of the function, if integral. Undefined otherwise.
extern size_t CELUA_ExecuteFunctionAsync(const char* luacode, size_t parameter);

/// Gets a reference ID which can be used to call an existing lua function via CELUA_ExecuteFunctionByReference.
/// \param functionname The name of the function to obtain a reference to.
/// \return The function's unique integer ID.
int CELUA_GetFunctionReferenceFromName(const char *functionname);

/// Executes the function specified by reference id.
/// \param refid ID of the function to execute, obtained with CELUA_GetFunctionReferenceFromName.
/// \param paramcount Number of parameters to be passed to the function.
/// \param parameters An array of integer parameters which will be passed to the function.
/// \param async If true, the code will run in a seperate thread instead of the main thread.
/// \return The return value of the function, if integral. Undefined otherwise.
extern size_t CELUA_ExecuteFunctionByReference(int refid, size_t paramcount, const size_t* parameters, int async);

#endif