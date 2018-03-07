/*
MIT License

Copyright (c) 2018 Sebastián Tromer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
    int fd;
    const char *fifo_path = "/tmp/simple_fifo";

    std::cout << "Named Pipes - Simple writer" << std::endl;

    // Create FIFO special file at fifo_path
    fd = mkfifo(fifo_path, 0666);
    if (fd == -1) {
        std::cerr << "Cannot create fifo file at: " << fifo_path << std::endl;
        return EXIT_FAILURE;
    }

    // Opening the read or write end of a FIFO blocks until the other end is 
    // also opened (by another process or thread)
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        std::cerr << "Cannot open fifo file at: " << fifo_path << std::endl;
        return EXIT_FAILURE;
    }

    // Close and Remove the created FIFO special file from the system
    close(fd);
    unlink(fifo_path);
    return EXIT_SUCCESS;
}

