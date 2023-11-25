#include "pch.h"
#include "application.h"

int main(void)
{
  auto app = std::make_unique<Application>("JMeshBox");//唯一指针
  app->loop();

  return 0;
}
