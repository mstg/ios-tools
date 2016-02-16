// Prints all IOServices
#include <IOKit/IOKitLib.h>

int main(int argc, char * argv[]) {
  kern_return_t err;
  io_iterator_t i;
  err = IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("IOService"), &i);
  
  if (err != KERN_SUCCESS) {
    printf("IOServiceGetMatchingServices: error\n");
    exit(1);
  }
	
  io_service_t temp;
  kern_return_t kr;
  io_name_t serviceName;
  io_name_t service_before;
  int count = 0;
  
  printf("Print all services\n----------------\n");
  while(IOIteratorIsValid(i) && (temp = IOIteratorNext(i))) {
    kr = IORegistryEntryGetName(temp, serviceName);
    if (strcmp(service_before, serviceName) == 0) continue;
    strcpy(service_before, serviceName);
    if (kr != KERN_SUCCESS) {
      IOObjectRelease(temp);
      printf("Can't get name of service!\n");
      continue;
    }
		
    printf("%s\n", serviceName);
    count++;
  }
	
  printf("Count: %d\n", count);
	
  printf("\n");
}
