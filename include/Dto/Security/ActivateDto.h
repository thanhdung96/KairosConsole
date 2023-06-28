#ifndef ACTIVATEDTO_H
#define ACTIVATEDTO_H

#include "Dto/Security/BaseSecurityDto.h"
#include <string>

namespace DTO::Security
{
using std::string;

    class ActivateDto : public BaseSecurityDto
    {
        public:
            ActivateDto(string Username, string Hashcode);
            ActivateDto() = default;
            ~ActivateDto() override = default;

            string GetHashcode() { return m_Hashcode; }
            void SetHashcode(string val) { m_Hashcode = val; }

        protected:

        private:
            string m_Hashcode;
    };
}
#endif // ACTIVATEDTO_H
