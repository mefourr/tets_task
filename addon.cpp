#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <codecvt>
#include <locale>

using namespace Napi;

String CheckUserPrivilege(const CallbackInfo &info)
{
    Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString())
    {
        TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return String::New(env, "");
    }

    std::string userName = info[0].As<String>().Utf8Value();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideUserName = converter.from_bytes(userName);

    USER_INFO_1 *userInfo;
    DWORD dwLevel = 1;

    NET_API_STATUS nStatus = NetUserGetInfo(NULL, wideUserName.c_str(), dwLevel, (LPBYTE *)&userInfo);

    if (nStatus == NERR_Success)
    {
        std::wstring wsPrivilege;
        switch (userInfo->usri1_priv)
        {
        case USER_PRIV_ADMIN:
            wsPrivilege = L"Administrator";
            break;
        case USER_PRIV_USER:
            wsPrivilege = L"User";
            break;
        case USER_PRIV_GUEST:
            wsPrivilege = L"Guest";
            break;
        default:
            wsPrivilege = L"Unknown";
            break;
        }
        NetApiBufferFree(userInfo);

        std::string privilege(wsPrivilege.begin(), wsPrivilege.end());
        return String::New(env, "Пользователь " + userName + " имеет привелегию " + privilege);
    }
    else
    {
        if (userInfo != NULL)
        {
            NetApiBufferFree(userInfo);
        }
        std::string errorMessage = "Failed to retrieve user info. Error code: " + std::to_string(nStatus);
        return String::New(env, errorMessage);
    }
}

Object Init(Env env, Object exports)
{
    exports.Set(
        String::New(env, "checkUserPrivilege"),
        Function::New(env, CheckUserPrivilege));

    return exports;
}

NODE_API_MODULE(addon, Init)
