package id.web.witchcraft.house;
import android.app.job.JobParameters;
import android.app.job.JobService;
import android.content.Intent;

public class MyJobScheduler extends JobService {
    @Override
    public boolean onStartJob(JobParameters params) {
        //Intent service = new Intent(getApplicationContext(), LocalWordService.class);
        //getApplicationContext().startService(service);
        //Util.scheduleJob(getApplicationContext()); // reschedule the job
        //return true;

        Intent startServiceIntent = new Intent(getApplicationContext(), MyService.class);
        getApplicationContext().startService(startServiceIntent);
        MyUtility.scheduleJob(getApplicationContext()); // reschedule the job
        return true;
    }

    @Override
    public boolean onStopJob(JobParameters params) {
        return true;
    }
}
