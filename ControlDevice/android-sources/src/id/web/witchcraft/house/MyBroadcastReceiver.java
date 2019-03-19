package id.web.witchcraft.house;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.Context;

public class MyBroadcastReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        Intent startServiceIntent = new Intent(context, MyService.class);
        context.startService(startServiceIntent);
    }
}
