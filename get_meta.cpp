#include <iostream>
#include <Windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
int main()
{
	BOOL  bResults = FALSE;
	HINTERNET hSession = NULL,
	hConnect = NULL,
	hRequest = NULL;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"A WinHTTP Example Program/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, L"10.59.60.158", 40000, 0);

	// Create an HTTP Request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET",
			L"/sld/sld.svc/$metadata",
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);

	DWORD security_flag_value = SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
		SECURITY_FLAG_IGNORE_CERT_DATE_INVALID |
		SECURITY_FLAG_IGNORE_UNKNOWN_CA;

	bResults = ::WinHttpSetOption(
		hRequest,
		WINHTTP_OPTION_SECURITY_FLAGS,
		&security_flag_value,
		sizeof(security_flag_value));
	if (!bResults)
	{
		printf("Error %d has occurred.\n", GetLastError());
	}

	// Send a Request.
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0, WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);

	// Place additional code here.

	// Report errors.
	if (!bResults)
		printf("Error %d has occurred.\n", GetLastError());

	// Close open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
}
