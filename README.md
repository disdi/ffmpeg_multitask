To build the project

1. In the ffmpeg_multitask/libffmpeg-c/deps/FFmpeg/ 
   
   ./configure --disable-static --enable-shared --prefix=/home/aetelelink/ffmpeg_multitask/libffmpeg-c/
   
   sudo make 
   
   sudo make install

All the .so will get created in /home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib

2. Edit the LD_LIBRARY_PATH 
   
   export LD_LIBRARY_PATH=/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/:$LD_LIBRARY_PATH

3. In the ffmpeg_multitask/libffmpeg-c/ 
   
   sudo make 

   libffmpeg.so will get created in ffmpeg_multitask/libffmpeg-c/

4. In the ffmpeg_multitask/
   
   sudo make

   ffmpeg_multitask will get created in ffmpeg_multitask/ 

5. Run the final executable
   
   ./ffmpeg_multitask
