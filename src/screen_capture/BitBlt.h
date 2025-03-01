#pragma once

// Inject to screenCapture.exe to hook BitBlt function 
namespace seeob::screen {
    struct BitBlt {
        static void install();
    };
};