#ifndef ACTIVATEDTO_H
#define ACTIVATEDTO_H

#include <BaseSecurityDto.h>
#include <string>

namespace DTO
{
    namespace Security
    {
        using namespace std;
        class ActivateDto : public BaseSecurityDto
        {
            public:
                ActivateDto(string Username, string Hashcode);
                ActivateDto();
                virtual ~ActivateDto() override;

                string GetHashcode() { return m_Hashcode; }
                void SetHashcode(string val) { m_Hashcode = val; }

            protected:

            private:
                string m_Hashcode;
        };
    }
}


#endif // ACTIVATEDTO_H
