import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Thread
{
    private ServerSocket _serverSocket;
    private Socket _server = null;

    private PrintWriter _out = null;
    private BufferedReader _in = null;


    public Server()
    {
        try
        {
            _serverSocket = new ServerSocket(6817);
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }


    @Override
    @SuppressWarnings("InfiniteLoopStatement")
    public void run()
    {
        // Double infinite loops are totally intentional. Question, but move on (please)
        for(;;)
        {
            try
            {
                establishConnection();
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }

            for(;;)
            {
                try
                {
                    if(_server.isConnected())
                    {
                        _out.write("Hello from Java! Hey C++, I've also got a hecka long message! But these things take " +
                                "time so I'll just send a bunch of 0s. Here we go: 000000000000000000000000000000000000000" +
                                "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" +
                                "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" +
                                "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" +
                                " Wow that's a lot of 0s! That's at least two of them! Great job if you get every single one!");
                        _out.flush();
                        System.out.println("Sent!");

                        System.out.println(_in.readLine());
                    }
                    Thread.sleep(2000);
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                    break;
                }
            }
        }
    }


    private void establishConnection() throws IOException
    {
        _server = _serverSocket.accept();
        _in =  new BufferedReader(new InputStreamReader(_server.getInputStream()));
        _out = new PrintWriter(_server.getOutputStream());

        System.out.println("Client Connected!");
    }
}
