/********************************
 * 
 * Notes: Checksum 8 byte
 * 
 * Start 0 to the end
 * 
 * Example：  HEX
 * 
 * In  -> 12 34 
 * Out -> 12 34 46 
 * 
 *******************************/

(
    function main() {
        source = this.SourceDataBuffer; //Source data buffer;

        var buf = new ArrayBuffer(source.length + 1)
        var newBuffer = new Uint8Array(buf);

        newBuffer[newBuffer.length - 1] = 0;
        for (var i = 0; i < source.length; i++) {
            newBuffer[i] = source[i];
            newBuffer[newBuffer.length - 1] += source[i];
        }

        return newBuffer;
    }
)()



