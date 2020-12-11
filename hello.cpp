#include <iostream>
#include <filesystem>

// crashpad
#include <client/settings.h>
#include <client/crashpad_client.h>
#include "client/crash_report_database.h"

using namespace std;

bool startCrashpad(const filesystem::path& thisExecutable)
{
    using namespace crashpad;

    // based on https://docs.sentry.io/platforms/native/guides/crashpad/

    const auto tempDir = filesystem::temp_directory_path() / "hellocrashpad";
    cout << "temp dir: " << tempDir << "\n";

    const auto currentPath = thisExecutable.parent_path();
    cout << "current path: " << currentPath << "\n";

    base::FilePath handler(currentPath / "crashpad_handler");
    const string url("https://o490035.ingest.sentry.io/api/5553252/minidump/?sentry_key=fa1fcd75f3954bb383fb531939ad6d2f");
    map<string, string> annotations;
    vector<string> arguments;

    // only for testing, remove in production
    arguments.push_back("--no-rate-limit");

    base::FilePath database(tempDir);
    unique_ptr<CrashReportDatabase> db = CrashReportDatabase::Initialize(database);

    if (db != nullptr && db->GetSettings() != nullptr) {
        db->GetSettings()->SetUploadsEnabled(true);
    }

    CrashpadClient client;
    bool success = client.StartHandler(handler, database, database, url, annotations,
        arguments, /* restartable */ true, /* asynchronous_start */ false);

    return success;
}

int main(int argc, char* argv[])
{
    const bool crashpadStarted = startCrashpad(argv[0]);
    cout << "crashpad started: " << crashpadStarted << "\n";

    cout << "--- crash it! ---\n";
    int* p = nullptr;
    cout << p[0];
}
