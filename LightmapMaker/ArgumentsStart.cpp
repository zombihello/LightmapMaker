#include "ArgumentsStart.h"
#include <thread>

//-------------------------------------------------------------------------//

bool		ArgumentsStart::IsDisableShadow		=	false;
bool		ArgumentsStart::IsSaveLog			=	false;
int			ArgumentsStart::MaxSizeLightmap		=	16;
int			ArgumentsStart::NumberThreads		=	thread::hardware_concurrency();
string		ArgumentsStart::RouteToMap			=	"";

//-------------------------------------------------------------------------//