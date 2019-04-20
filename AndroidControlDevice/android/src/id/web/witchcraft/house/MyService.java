package id.web.witchcraft.house;
import org.qtproject.qt5.android.bindings.QtService;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.app.AlarmManager;
import android.os.SystemClock;

public class MyService extends QtService{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static MyService m_instance;

    public MyService()
    {
        m_instance = this;
    }

    public static void startMyService(Context ctx) {
        ctx.startService(new Intent(ctx, MyService.class));
        MyUtility.scheduleJob(ctx);
    }

    public static void notify(int id,String title,String body) {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(MyService.NOTIFICATION_SERVICE);
        }

        Intent notificationIntent = new Intent(m_instance, MyActivity.class);
        //notificationIntent.setAction(Constants.ACTION.MAIN_ACTION);
        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
        PendingIntent pendingIntent = PendingIntent.getActivity(m_instance, 0, notificationIntent, 0);

        m_builder = new Notification.Builder(m_instance);
        m_builder.setSmallIcon(R.drawable.icon);
        m_builder.setContentTitle(title);
        m_builder.setContentText(body);
        m_builder.setContentIntent(pendingIntent);
        //m_builder.flags |= Notification.FLAG_AUTO_CANCEL;
        m_notificationManager.notify(id, m_builder.build());
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        //[the notification]
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(MyService.NOTIFICATION_SERVICE);
        }
        Intent notificationIntent = new Intent(m_instance, MyActivity.class);
        //notificationIntent.setAction(Constants.ACTION.MAIN_ACTION);
        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
        PendingIntent pendingIntent = PendingIntent.getActivity(m_instance, 0, notificationIntent, 0);

        m_builder = new Notification.Builder(m_instance);
        m_builder.setSmallIcon(R.drawable.icon);
        m_builder.setContentTitle("Witchcraft House");
        m_builder.setContentText("Witchcraft House Service is On");
        m_builder.setOngoing(true);
        m_builder.setContentIntent(pendingIntent);
        //m_builder.flags |= Notification.FLAG_AUTO_CANCEL;
        //m_notificationManager.notify(1, m_builder.build());
        startForeground(1,m_builder.build());
        //[the notification]

        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        sendBroadcast(new Intent("WitchcraftServiceNeedRestart"));
        //MyUtility.scheduleJob(getApplicationContext());
    }

    @Override
    public void onTaskRemoved(Intent rootIntent) {
        super.onDestroy();
        sendBroadcast(new Intent("WitchcraftServiceNeedRestart"));
        //MyUtility.scheduleJob(getApplicationContext());
    }

}
