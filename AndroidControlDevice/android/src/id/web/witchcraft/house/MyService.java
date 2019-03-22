package id.web.witchcraft.house;
import org.qtproject.qt5.android.bindings.QtService;
import android.content.Context;
import android.content.Intent;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;

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
    }

    public static void notify(int id,String title,String body) {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(MyService.NOTIFICATION_SERVICE);
        }

        m_builder = new Notification.Builder(m_instance);
        m_builder.setSmallIcon(R.drawable.icon);
        m_builder.setContentTitle(title);
        m_builder.setContentText(body);
        m_notificationManager.notify(id, m_builder.build());
    }
}
