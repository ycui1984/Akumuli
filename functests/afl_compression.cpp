#include "storage_engine/compression.h"
#include "util.h"

#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <zlib.h>
#include <cstring>

using namespace Akumuli;

int main(int argc, char** argv) {
    if (argc == 1) {
        return 1;
    }
    std::string file_name(argv[1]);
    std::fstream input(file_name, std::ios::binary|std::ios::in|std::ios::out);
    UncompressedChunk header;

    double tx;
    aku_Timestamp ts;
    while(input) {
        input.read(reinterpret_cast<char*>(&ts), sizeof(ts));
        if (input) {
            input.read(reinterpret_cast<char*>(&tx), sizeof(tx));
        }
        if (input) {
            header.timestamps.push_back(ts);
            header.values.push_back(tx);
        }
    }

    ByteVector buffer(32 + header.timestamps.size()*10, 0);
    StorageEngine::DataBlockWriter writer(42, buffer.data(), static_cast<int>(buffer.size()));

    for (u32 i = 0; i < header.timestamps.size(); i++) {
        aku_Status status = writer.put(header.timestamps.at(i), header.values.at(i));
        if (status != AKU_SUCCESS) {
            AKU_PANIC("Can't compress data: " + std::to_string(status));
        }
    }

    StorageEngine::DataBlockReader reader(buffer.data(), buffer.size());
    for (u32 i = 0; i < header.timestamps.size(); i++) {
        aku_Timestamp ts;
        double tx;
        aku_Status status;
        std::tie(status, ts, tx) = reader.next();
        if (status != AKU_SUCCESS) {
            AKU_PANIC("Can't decompress data: " + std::to_string(status));
        }
        if (ts != header.timestamps.at(i)) {
            AKU_PANIC("Bad timestamp at: " + std::to_string(i));
        }
        if (tx != header.values.at(i)) {
            AKU_PANIC("Bad value at: " + std::to_string(i));
        }
    }
    return 0;
}