internal static class ConnectionCreator
{
    static void Main(string[] args)
    {
        Client client = new Client("ffurm07114", "ctor63931L");

        while (true)
        {
            if(client.Failed())
            {
                Console.WriteLine($"Account {client.GetUsername()} failed");
            }

            client.RunCallbacks();
        } 
    }
}