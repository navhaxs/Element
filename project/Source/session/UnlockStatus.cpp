
#include "session/UnlockStatus.h"
#include "Globals.h"
#include "Settings.h"

#define EL_LICENSE_SETTINGS_KEY "L"

#if EL_USE_LOCAL_AUTH
 #define EL_PRODUCT_ID "15"
 #define EL_BASE_URL "http://kushview.dev"
 #define EL_AUTH_URL EL_BASE_URL "/edd-cp"
// #define EL_PUBKEY "5,b2edd6e3c5e596716bc7323d07faca55"
 #define EL_PUBKEY "c7e1,85dd0da1f1626aa9fc96ae5834fb954d87a840c0d4c0fe293825105ef7121ef7adb85171679d8e672c967d913cece7e10ec392524c0d065a4451553a87edfb75"
#else
 #define EL_PRODUCT_ID "20"
 #define EL_BASE_URL "https://kushview.net"
 #define EL_AUTH_URL EL_BASE_URL "/products/authorize"
 #define EL_PUBKEY "5,c72ce63fbe64d394711f0623ee2efa749f59e192cc87ed440bab12d9f2c8cc67e0464ad18b483c171e8e9762e1a14106348f633e7acde5ec9271e9927582df02816b65d3f836d5a7a46baa3af530adec166fdc0c68320ba68d5e21ca493772753c834388fbf7d21f3e38bc3b8b7ac917cb396c1579ce9e347215fc1b1e837d099f46d9a8c422369f64d93c3f18d85e20895f244192abc1919da275eb3cebc15655f2be9e9ee97298fb8fd21c33b01d9f1849ac6ba2e1d91852847a675c6f4e2c7f00d6f4f29db9357c8fdf4af9484da07018ab986ee6ad9c88ba5a724cb98751c6c0ccbbd94c9d70a90d3cec7f8f9a42463f1df6c342c5f2dd272cf112c204f5"
#endif

namespace Element {
    UnlockStatus::UnlockStatus (Globals& g) : settings (g.getSettings()) { }
    String UnlockStatus::getProductID() { return EL_PRODUCT_ID; }
    bool UnlockStatus::doesProductIDMatch (const String& returnedIDFromServer)
    {
        return getProductID() == returnedIDFromServer;
    }
    
    RSAKey UnlockStatus::getPublicKey() { return RSAKey (EL_PUBKEY); }
    
    void UnlockStatus::saveState (const String& data)
    {
        if (auto* const props = settings.getUserSettings())
            props->setValue (EL_LICENSE_SETTINGS_KEY, data);
    }
    
    String UnlockStatus::getState()
    {
        if (auto* const props = settings.getUserSettings())
        {
            const String value =  props->getValue (EL_LICENSE_SETTINGS_KEY).toStdString();
            eddRestoreState (value);
            return value;
        }
        return String();
    }
    
    String UnlockStatus::getWebsiteName() {
        return "Kushview";
    }
    
    URL UnlockStatus::getServerAuthenticationURL() {
        const URL authurl (EL_AUTH_URL);
        return authurl;
    }
    
    StringArray UnlockStatus::getLocalMachineIDs()
    {
        auto ids (OnlineUnlockStatus::getLocalMachineIDs());
        return ids;
    }
}
