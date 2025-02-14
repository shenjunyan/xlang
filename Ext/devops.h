#pragma once
#include "xpackage.h"
#include "function.h"
#include "runtime.h"
#include <vector>
#include <iostream>
namespace X
{
	/*
		About this design pattern
		from assmeblly code,Start function inside mImpl
		will be inlined in released version with optimization 
	*/
	namespace DevOps
	{
		class DebugService
		{
			bool BuildStackInfo(
				XlangRuntime* rt,
				XObj* pContextCurrent,
				AST::CommandInfo* pCommandInfo,
				X::Value& valStackInfo);
			bool PackScopeVars(XlangRuntime* rt, 
				XObj* pContextCurrent, AST::Scope* pScope,
				X::Value& varPackList);
			bool PackScopeSpecialVars(XlangRuntime* rt,
				XObj* pContextCurrent, AST::Scope* pScope,
				X::Value& varPackList);
			bool BuildGlobals(XlangRuntime* rt,
				XObj* pContextCurrent,
				X::Value& valGlobals);
			bool BuildLocals(XlangRuntime* rt,
				XObj* pContextCurrent, int frameId,
				X::Value& valLocals);
			bool BuildObjectContent(XlangRuntime* rt,
				XObj* pContextCurrent, int frameId, X::Value& valParam,
				X::Value& valObject);
			bool ObjectSetValue(XlangRuntime* rt,
				XObj* pContextCurrent, int frameId, X::Value& valParam,
				X::Value& objRetValue);
		public:
			BEGIN_PACKAGE(DebugService)
				APISET().AddFunc<1>("get_startline", &DebugService::GetModuleStartLine);
				APISET().AddRTFunc<2>("set_breakpoints", &DebugService::SetBreakpoints);
				APISET().AddVarFunc("command", &DebugService::Command);
			END_PACKAGE
			DebugService();
			int GetModuleStartLine(unsigned long long moduleKey);
			X::Value SetBreakpoints(X::XRuntime* rt,X::XObj* pContext,
				unsigned long long moduleKey, Value& varLines);
			bool Command(X::XRuntime* rt, X::XObj* pContext,
				ARGS& params,
				KWARGS& kwParams,
				X::Value& retValue);
		};
	}
}