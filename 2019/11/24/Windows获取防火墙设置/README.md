<!--
{
	"author": "lxf",
	"title": "Windows获取防火墙设置",
	"date": "2019-11-24 20:21:16",
	"category": "Windows核心编程"
}
-->

Windows获取防火墙设置
------------------------------------------------------------
2019-11-24 20:21:16 &emsp;   

```
/********************************************************************++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) Microsoft. All Rights Reserved.

Abstract:
    This C++ file includes sample code for reading Windows Firewall 
    Settings per profile using the Microsoft Windows Firewall APIs.

--********************************************************************/

#include <windows.h>
#include <stdio.h>
#include <netfw.h>

#pragma comment( lib, "ole32.lib" )


// Forward declarations
void        Get_FirewallSettings_PerProfileType(NET_FW_PROFILE_TYPE2 ProfileTypePassed, INetFwPolicy2* pNetFwPolicy2);
HRESULT     WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);


int __cdecl main()
{
    HRESULT hrComInit = S_OK;
    HRESULT hr = S_OK;

    INetFwPolicy2 *pNetFwPolicy2 = NULL;

    // Initialize COM.
    hrComInit = CoInitializeEx(
                    0,
                    COINIT_APARTMENTTHREADED
                    );

    // Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
    // initialized with a different mode. Since we don't care what the mode is,
    // we'll just use the existing mode.
    if (hrComInit != RPC_E_CHANGED_MODE)
    {
        if (FAILED(hrComInit))
        {
            printf("CoInitializeEx failed: 0x%08lx\n", hrComInit);
            goto Cleanup;
        }
    }

    // Retrieve INetFwPolicy2
    hr = WFCOMInitialize(&amp;pNetFwPolicy2);
    if (FAILED(hr))
    {
        goto Cleanup;
    }

    printf("Settings for the firewall domain profile:\n");
    Get_FirewallSettings_PerProfileType(NET_FW_PROFILE2_DOMAIN, pNetFwPolicy2);

    printf("Settings for the firewall private profile:\n");
    Get_FirewallSettings_PerProfileType(NET_FW_PROFILE2_PRIVATE, pNetFwPolicy2);

    printf("Settings for the firewall public profile:\n");
    Get_FirewallSettings_PerProfileType(NET_FW_PROFILE2_PUBLIC, pNetFwPolicy2);

Cleanup:

    // Release INetFwPolicy2
    if (pNetFwPolicy2 != NULL)
    {
        pNetFwPolicy2->Release();
    }

    // Uninitialize COM.
    if (SUCCEEDED(hrComInit))
    {
        CoUninitialize();
    }
   
    return 0;
}

void Get_FirewallSettings_PerProfileType(NET_FW_PROFILE_TYPE2 ProfileTypePassed, INetFwPolicy2* pNetFwPolicy2)
{
    VARIANT_BOOL bIsEnabled = FALSE;
    NET_FW_ACTION action;

    printf("******************************************\n");   

    if(SUCCEEDED(pNetFwPolicy2->get_FirewallEnabled(ProfileTypePassed, &amp;bIsEnabled)))
    {
        printf ("Firewall is %s\n", bIsEnabled ? "enabled" : "disabled");
    }

    if(SUCCEEDED(pNetFwPolicy2->get_BlockAllInboundTraffic(ProfileTypePassed, &amp;bIsEnabled)))
    {
        printf ("Block all inbound traffic is %s\n", bIsEnabled ? "enabled" : "disabled");
    }

    if(SUCCEEDED(pNetFwPolicy2->get_NotificationsDisabled(ProfileTypePassed, &amp;bIsEnabled)))
    {
        printf ("Notifications are %s\n", bIsEnabled ? "disabled" : "enabled");
    }

    if(SUCCEEDED(pNetFwPolicy2->get_UnicastResponsesToMulticastBroadcastDisabled(ProfileTypePassed, &amp;bIsEnabled)))
    {
        printf ("UnicastResponsesToMulticastBroadcast is %s\n", bIsEnabled ? "disabled" : "enabled");
    }

    if(SUCCEEDED(pNetFwPolicy2->get_DefaultInboundAction(ProfileTypePassed, &amp;action)))
    {
        printf ("Default inbound action is %s\n", action != NET_FW_ACTION_BLOCK ? "Allow" : "Block");
    }

    if(SUCCEEDED(pNetFwPolicy2->get_DefaultOutboundAction(ProfileTypePassed, &amp;action)))
    {
        printf ("Default outbound action is %s\n", action != NET_FW_ACTION_BLOCK ? "Allow" : "Block");
    }

    printf("\n");
}


// Instantiate INetFwPolicy2
HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2)
{
    HRESULT hr = S_OK;

    hr = CoCreateInstance(
        __uuidof(NetFwPolicy2), 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        __uuidof(INetFwPolicy2), 
        (void**)ppNetFwPolicy2);

    if (FAILED(hr))
    {
        printf("CoCreateInstance for INetFwPolicy2 failed: 0x%08lx\n", hr);
        goto Cleanup;        
    }

Cleanup:
    return hr;
}
```

参考文献  

[1][Getting Firewall Settings](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ics/c-getting-firewall-settings)  

------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)&emsp;|&emsp;[返回首页](./../../../../README.md)