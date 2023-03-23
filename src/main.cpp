#include <iostream>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
using namespace std;
int main()
{
    std::cout << "hello" << endl;
    av_register_all();
//    avcodec_register_all();
//    AVFormatContext *avFormatContext = avformat_alloc_context();
//    if (avFormatContext)
//    {
//        cout << "call ffmpeg avformat_alloc_context\n"
//             << endl;
//    }
    return 0;
}
