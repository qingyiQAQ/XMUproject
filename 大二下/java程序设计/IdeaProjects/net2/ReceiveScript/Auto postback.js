/********************************
 * 
 * Notes: Auto postback
 * 
 * The received data is automatically sent back.
 * 
 * 
 *******************************/

(
    function main() {
        var str=receive.get(); //Read the Received string.
        receive.write(str);  //Show received string.
        if(receive.isHexDisplay()==true)
            send.write(str,true) //hex string
        else
            send.write(str);  //Send received string.
        return ;
    }
)()


