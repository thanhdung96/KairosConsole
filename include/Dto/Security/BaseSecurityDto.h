#ifndef BASESECURITYDTO_H
#define BASESECURITYDTO_H

#include <string>

namespace DTO
{
    namespace Security
    {
        using namespace std;
        class BaseSecurityDto
        {
            public:
                virtual ~BaseSecurityDto();

                string GetUsername() { return m_Username; }
                void SetUsername(string val) { m_Username = val; }

            protected:
                BaseSecurityDto(string Username);

                string m_Username;
        };
    }
}
#endif // BASESECURITYDTO_H
