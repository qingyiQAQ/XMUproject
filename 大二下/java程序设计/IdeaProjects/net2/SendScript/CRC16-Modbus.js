/********************************
 * 
 * Notes: CRC16-Modbus
 * 
 * x16+x15+x2+1    0x8005 -> 0xA001         
 *                 0x1021 -> 0x8408
 * 
 * Example： HEX
 * 
 * In -> 12 34 
 * Out-> 12 34 0C C7
 * 
 *******************************/

(
    function main() {
        source = this.SourceDataBuffer; //Source data buffer;
        var buf = new ArrayBuffer(source.length + 2); //Create a new array
        var newBuffer = new Uint8Array(buf);

        //Adding check
        for (var i = 0; i < source.length; i++)
            newBuffer[i] = source[i];

        var crc = 0xFFFF;
        for (var i = 0; i < source.length; i++) {
            crc ^= (source[i] & 0x00FF);
            for (var j = 0; j < 8; j++) {
                if (crc & 0x01) {
                    crc >>= 1;
                    crc ^= 0xA001;
                }
                else
                    crc >>= 1;
            }
        }
        newBuffer[source.length] = crc;
        newBuffer[source.length + 1] = crc >> 8;
        return newBuffer;
    }
)()

