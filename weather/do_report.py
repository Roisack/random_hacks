import os
import shutil
import time
import subprocess
from subprocess import Popen, PIPE, STDOUT

class WeatherEntry:

    def __init__(self, city, data, valid=True):
        self.name = city
        self.temperature = "No data received"
        self.celsius = -999
        self.wind = ""
        self.humidity = ""
        self.conditions = ""
        self.is_max = False
        self.is_min = False

        self.is_valid = valid
        if (self.is_valid == False):
            return

        lines = data.split('\n')

        for l in lines:
            if ("Temperature" in l):
                self.temperature = l
                try:
                    temp_str = self.temperature[self.temperature.find("(")+1:self.temperature.find(")")]
                    self.celsius = float(temp_str[:-1])
                except Exception as e:
                    print("error convertin temperature to float: " + str(e))
            if ("Wind" in l):
                self.wind = l
            if ("Relative Humidity" in l):
                self.humidity = l
            if ("Sky conditions" in l):
                self.conditions = l

def write_row(data):
    f = open('./report.html', 'a')

    if (data.is_min):
        f.write("<tr><td class=\"is_min\">")
    elif (data.is_max):
        f.write("<tr><td class=\"is_max\">")
    else:
        f.write("<tr><td>")
    f.write(data.name)
    f.write("</td><td>")
    f.write(data.temperature)
    f.write("</td><td>")
    f.write(data.humidity)
    f.write("</td><td>")
    f.write(data.wind)
    f.write("</td><td>")
    f.write(data.conditions)
    f.write("</td></tr>")

    f.close()

def write_error(city):
    f = open('./report.html', 'a')
    f.write("<tr><td>")
    f.write(city)
    f.write("</td><td>No data received")
    f.write("</td><td></td><td></td><td></td></tr>")
    f.close()

def finish_document():
    print("Finishing document")
    f = open('./report.html', 'a')
    f.write("</table><br><br>")

    output = ""
    process = os.popen("/bin/date", "r")
    while 1:
        line = process.readline()
        if not line: break
        output += line
    f.write("Data generated ")
    f.write(output)
    f.write("</body></html>")
    f.close()


def fetch_data(code): 
    cmdline = ["/home/gekko/weather/weather-2.2/weather", code]

    output = None
    try:
        output = subprocess.check_output(cmdline)
    except Exception as e:
        raise Exception("Error retrieving data")
    print(output)
    return output

def do_report(city, code):
    trying = True
    tries = 1
    output = None
    while (trying == True):
        try:
            print("Fetching data (#attempt " + str(tries) + ")")
            output = fetch_data(code)
            trying = False
        except Exception as e:
            print(e)
            tries += 1
            if (tries >= 4):
                trying = False
                print("Giving up after 4 tries. Writing error to output")
                return WeatherEntry(city, "", False)
    time.sleep(1)
    return WeatherEntry(city, output)

def prepare():
    try:
        shutil.copy("./template.html", "./report.html")
        print("Successfully copied template file")
    except IOError as e:
        print(e)

def upload():
    try:
        shutil.copy("./report.html", "/home/gekko/public_html/weather/index.html")
        print("Successfully uploaded the report")
        os.chmod("/home/gekko/public_html/weather/index.html", 0775)
    except IOError as e:
        print(e)

def findMinMax(results):
    if (len(results) <= 0):
        return results

    current_min = 0
    current_max = 0

    for i in range(0, len(results)):
        if (results[i].is_valid == False):
            continue
        if (results[i].celsius < results[current_min].celsius):
            current_min = i
        if (results[i].celsius > results[current_max].celsius):
            current_max = i

    results[current_min].is_min = True
    results[current_max].is_max = True

    print("coldest: " + results[current_min].name)
    print("hottest: " + results[current_max].name)

    return results

def output_results(results):
    for r in results:
        write_row(r)

prepare()

results = []
# ICAO codes
results.append(do_report("Clarksville (Ranti)", "KCKV"))
results.append(do_report("Bagotville (Blue)", "CYBG"))
results.append(do_report("Helsinki (Gekko)", "EFHK"))
results.append(do_report("Tampere", "EFTP"))
results.append(do_report("Kuopio", "EFKU"))
results.append(do_report("Moscow (Xai)", "UUEE"))
results.append(do_report("Palanga (Rytis)", "EYPA"))
results.append(do_report("Kansas City (Dritz)", "KMCI"))
results.append(do_report("North Vancouver (AmonX)", "CYVR"))
results.append(do_report("Detroit (Oldlaptop)", "KDTW"))
results.append(do_report("Minneapolis (Captain)", "KMSP"))
results.append(do_report("Miami (Ziper)", "KMIA"))
results.append(do_report("Florianopolis (Yohan)", "SBFL"))
results.append(do_report("Lisboa (SlowIdent)", "LPPT"))
results.append(do_report("Chennai", "VOMM"))
results.append(do_report("Dusseldorf (Vrad)", "EDDL"))
results.append(do_report("Melbourne (chaos95)", "YMML"))

results = findMinMax(results)
output_results(results)

finish_document()
upload()

