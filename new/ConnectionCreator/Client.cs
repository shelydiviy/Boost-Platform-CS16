using SteamKit2;
using SteamKit2.GC.CSGO.Internal;
using SteamKit2.Internal;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

internal class Client
{
    private static SteamClient m_Client;
    private static SteamUser m_User;
    private static CallbackManager m_CallbackManager;
    
    private static string m_Username;
    private static string m_Password;
    private static bool m_Connected;
    private static bool m_ShouldDelete;

    public Client(string username, string password)
    {
        m_Username = username;
        m_Password = password;

        m_Client = new SteamClient();
        m_CallbackManager = new CallbackManager(m_Client);

        m_CallbackManager.Subscribe<SteamClient.ConnectedCallback>(OnConnected);
        m_CallbackManager.Subscribe<SteamClient.DisconnectedCallback>(OnDisconnected);
        m_CallbackManager.Subscribe<SteamUser.LoggedOnCallback>(OnLoggedOn);
        m_CallbackManager.Subscribe<SteamUser.LoggedOffCallback>(OnLoggedOff);
        m_CallbackManager.Subscribe<SteamUser.AccountInfoCallback>(onAccountInfo);

        m_Client.Connect();
    }

    private void onAccountInfo(SteamUser.AccountInfoCallback callback)
    {
        m_Client.GetHandler<SteamFriends>().SetPersonaState(EPersonaState.Online);

        m_Client.GetHandler<GCClient>()
    }

    public void RunCallbacks()
    {
        m_CallbackManager.RunWaitCallbacks(TimeSpan.FromSeconds(1));
    }

    public bool Failed()
    {
        return m_ShouldDelete;
    }

    public string GetUsername()
    {
        return m_Username;
    }

    private void OnConnected(SteamClient.ConnectedCallback callback)
    {
        m_Connected = true;
        
        Console.WriteLine($"Account {m_Username} has been connected to Steam network. Logging in..");

        var steamUser = m_Client.GetHandler<SteamUser>();

        if(steamUser == null)
        {
            m_ShouldDelete = true;
            Console.WriteLine($"Failed to initialize SteamUser for account ${m_Username}");
            return;
        }

        steamUser.LogOn(new SteamUser.LogOnDetails
        {
            Username = m_Username,
            Password = m_Password
        });

        m_User = steamUser;
    }
    private void OnDisconnected(SteamClient.DisconnectedCallback callback)
    {
        if(m_Connected)
        {
            Console.WriteLine($"Account {m_Username} has been disconnected from Steam network.");
        }
        else
        {
            Console.WriteLine($"Account {m_Username} could not be connected to Steam network");
            m_ShouldDelete = true;
            return;
        }
    }

    

    private void OnLoggedOn(SteamUser.LoggedOnCallback callback)
    {
        Console.WriteLine($"Account {m_Username} has been logged in Steam network");

        Console.WriteLine("Account details:");
        Console.WriteLine($"- SteamID: {m_Client.SteamID}");
        /*        Console.WriteLine($"- Password: {m_User.Password}");
                Console.WriteLine($"- CellID: {m_User.CellID}");
                Console.WriteLine($"- LoginID: {m_User.LoginID}");
                Console.WriteLine($"- AuthCode: {m_User.AuthCode}");
                Console.WriteLine($"- AccessToken: {m_User.AccessToken}");
                Console.WriteLine($"- AccountInstance: {m_User.AccountInstance}");
                Console.WriteLine($"- AccountID: {.AccountID}");*/

        var request = new ClientMsgProtobuf<CMsgClientGamesPlayed>(EMsg.ClientGamesPlayed);

        request.Body.games_played.Add(
            new CMsgClientGamesPlayed.GamePlayed
            {
                game_id = new GameID(10)
            }
            ); ;


        m_Client.Send(request);
    }
    private void OnLoggedOff(SteamUser.LoggedOffCallback callback)
    {
        Console.WriteLine($"Account {m_Username} has been logged off from Steam network");
    }

}
