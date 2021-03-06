#pragma once

#include <keyboard_client/cl_keyboard.h>
#include <smacc/smacc_orthogonal.h>
namespace sm_pr2_plugs{

class OrKeyboard : public smacc::Orthogonal<OrKeyboard>
{
public:
    virtual void onInitialize() override
    {
        auto clKeyboard = this->createClient<keyboard_client::ClKeyboard>();
        
        //ClKeyboard.queueSize = 1;
        clKeyboard->initialize();
    }
};
} // namespace sm_pr2_plugs