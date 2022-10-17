#include <all.h>   

#ifdef _WIN32
#include <processthreadsapi.h>
#endif


int main(int argc, char *argv[]) {
    tracklist *tracks = cd_rip_init(WAV, true);
}