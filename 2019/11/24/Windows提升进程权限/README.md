<!--
{
	"author": "lxf",
	"title": "Windows提升进程权限",
	"date": "2019-11-24 22:11:20",
	"category": "Windows核心编程"
}
-->

Windows提升进程权限
------------------------------------------------------------
2019-11-24 22:11:20 &emsp;   

```
NTSTATUS WINAPI RtlAdjustPrivilege(ULONG Privilege,
	BOOLEAN Enable,
	BOOLEAN CurrentThread,
	PBOOLEAN Enabled)
{
	TOKEN_PRIVILEGES NewState;
	TOKEN_PRIVILEGES OldState;
	ULONG ReturnLength;
	HANDLE TokenHandle;
	NTSTATUS Status;

	TRACE("(%d, %s, %s, %p)\n", Privilege, Enable ? "TRUE" : "FALSE",
		CurrentThread ? "TRUE" : "FALSE", Enabled);

	if (CurrentThread)
	{
		Status = NtOpenThreadToken(GetCurrentThread(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			FALSE,
			&TokenHandle);
	}
	else
	{
		Status = NtOpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&TokenHandle);
	}

	if (!NT_SUCCESS(Status))
	{
		WARN("Retrieving token handle failed (Status %x)\n", Status);
		return Status;
	}

	OldState.PrivilegeCount = 1;

	NewState.PrivilegeCount = 1;
	NewState.Privileges[0].Luid.LowPart = Privilege;
	NewState.Privileges[0].Luid.HighPart = 0;
	NewState.Privileges[0].Attributes = (Enable) ? SE_PRIVILEGE_ENABLED : 0;

	Status = NtAdjustPrivilegesToken(TokenHandle,
		FALSE,
		&NewState,
		sizeof(TOKEN_PRIVILEGES),
		&OldState,
		&ReturnLength);
	NtClose(TokenHandle);
	if (Status == STATUS_NOT_ALL_ASSIGNED)
	{
		TRACE("Failed to assign all privileges\n");
		return STATUS_PRIVILEGE_NOT_HELD;
	}
	if (!NT_SUCCESS(Status))
	{
		WARN("NtAdjustPrivilegesToken() failed (Status %x)\n", Status);
		return Status;
	}

	if (OldState.PrivilegeCount == 0)
		*Enabled = Enable;
	else
		*Enabled = (OldState.Privileges[0].Attributes & SE_PRIVILEGE_ENABLED);

	return STATUS_SUCCESS;
}

BOOL EnhanceProcPrivilegeByRtlAdjustPrivilege()
{
	HANDLE token;
	//提升权限
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
	{
		MessageBox(NULL, L"打开进程令牌失败...", L"错误", MB_ICONSTOP);
		return FALSE;
	}
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	int res = ::LookupPrivilegeValueW(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	if (!res)
		return FALSE;
	HMODULE hNtDll = LoadLibraryW(L"ntdll.dll");
	if (!hNtDll)
		return FALSE;
	typedef int(__stdcall *PRtlAdjustPrivilege)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
	PRtlAdjustPrivilege RtlAdjustPrivilege = (PRtlAdjustPrivilege)GetProcAddress(hNtDll, "RtlAdjustPrivilege");
	if (RtlAdjustPrivilege)
	{
		BOOLEAN enabled = 0;
		//const unsigned long SE_DEBUG_PRIVILEGE = 0x14;
		res = RtlAdjustPrivilege(tkp.Privileges[0].Luid.LowPart, TRUE, FALSE, &enabled);
	}
	FreeLibrary(hNtDll);
	return TRUE;
}

BOOL EnhanceProcPrivilegeByAdjustTokenPrivileges()
{
	HANDLE token;
	//提升权限
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
	{
		MessageBox(NULL, L"打开进程令牌失败...", L"错误", MB_ICONSTOP);
		return FALSE;
	}
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	int res = ::LookupPrivilegeValueW(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	if (!res)
		return FALSE;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(token, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		MessageBox(NULL, L"调整令牌权限失败...", L"错误", MB_ICONSTOP);
		return FALSE;
	}
	__try {
		CloseHandle(token);
	} __except (EXCEPTION_EXECUTE_HANDLER) {};
	return TRUE;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)&emsp;|&emsp;[返回首页](./../../../../README.md)