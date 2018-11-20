import subprocess
import re
import os
from math import sqrt
import sys

# SETTINGS
PROG = "./produce.out"
# FOR TESTING: reduce this number when debugging
X = 500  # number of times to repeat the test

# This data structure holds the raw data for each test run
times = []

DEBUG = True

def call_produce(program, cmd_str, num_repeat_calls):
    '''
    This function calls the program `PROG`, with the commands provided by `cmds`, `X` number of times.
    The timing provided by the program (printed on the last line) will be saved in the `times` global variable.

    @param `program` string to the program `produce` to run
    @param `cmd_str` is a string containing the parameters to send to `program`
    '''
    print 'Calling "{} {}", {} times'.format(program, cmd_str, num_repeat_calls)

    my_times = []
    for i in xrange(num_repeat_calls):
        output = subprocess.check_output('{} {}'.format(program, cmd_str), stderr=subprocess.STDOUT, shell=True)
        matchObj = re.search(r'System execution time: ([0-9.]+) seconds', output)
        if matchObj:
            if DEBUG and i==0:
                print ' > First Returned Time: {} sec'.format(matchObj.group(1))
            my_times.append(1000.0 * float(matchObj.group(1)))
        else:
            print '\nError trying to find time for the following output:'
            print output
            quit(1)
        if i % 10 == 0:
            print '.',
            sys.stdout.flush()
    times.append({'cmd':cmd_str, 'times':my_times})
    print ''





def generate_test_data():
    '''
    Calls the specific test cases asked for by the lab.
    '''
    test_cases = [

        ###########################################
        # Change the buffer size
        #{'N':100, 'B':1, 'P':1, 'C':1},
        {'N':100, 'B':1, 'P':1, 'C':2},
        #{'N':100, 'B':1, 'P':1, 'C':3}, 
       
        #{'N':100, 'B':1, 'P':2, 'C':1},
        #{'N':100, 'B':1, 'P':3, 'C':1}, 

        #{'N':100, 'B':1, 'P':2, 'C':2},
        #{'N':100, 'B':1, 'P':3, 'C':3},

        # N=100, B=4
        #{'N':100, 'B':4, 'P':1, 'C':1},
        #{'N':100, 'B':4, 'P':1, 'C':2},
        #{'N':100, 'B':4, 'P':1, 'C':3}, 
        
        #{'N':100, 'B':4, 'P':2, 'C':1},
        #{'N':100, 'B':4, 'P':3, 'C':1}, 

        #{'N':100, 'B':4, 'P':2, 'C':2},
        #{'N':100, 'B':4, 'P':3, 'C':3},
        
        # N=100, B=50
        #{'N':100, 'B':50, 'P':1, 'C':1},
        #{'N':100, 'B':50, 'P':1, 'C':2},
        #{'N':100, 'B':50, 'P':1, 'C':3}, 
        
        #{'N':100, 'B':50, 'P':2, 'C':1},
        #{'N':100, 'B':50, 'P':3, 'C':1}, 

        #{'N':100, 'B':50, 'P':2, 'C':2},
        #{'N':100, 'B':50, 'P':3, 'C':3},
 
        # N=100, B=100
        #{'N':100, 'B':100, 'P':1, 'C':1},
        #{'N':100, 'B':100, 'P':1, 'C':2},
       # {'N':100, 'B':100, 'P':1, 'C':3}, 
        
        #{'N':100, 'B':100, 'P':2, 'C':1},
        #{'N':100, 'B':100, 'P':3, 'C':1}, 

        #{'N':100, 'B':100, 'P':2, 'C':2},
        #{'N':100, 'B':100, 'P':3, 'C':3},
        
	# N=100, B = 150
	#{'N':100, 'B':150, 'P':1, 'C':1},
	#{'N':100, 'B':150, 'P':1, 'C':2},
	#{'N':100, 'B':150, 'P':1, 'C':3},

	#{'N':100, 'B':150, 'P':2, 'C':1},
	#{'N':100, 'B':150, 'P':3, 'C':1},

	#{'N':100, 'B':150, 'P':2, 'C':2},
	#{'N':100, 'B':150, 'P':3, 'C':3},

        ##############################################

        # Change number of items to produce 
        #############################
         # N = 0, B = 8
	#{'N':0, 'B':8, 'P':1, 'C':1},
	#{'N':0, 'B':8, 'P':1, 'C':2},
	#{'N':0, 'B':8, 'P':1, 'C':3},
	
	#{'N':0, 'B':8, 'P':2, 'C':1},
	#{'N':0, 'B':8, 'P':3, 'C':1},

	#{'N':0, 'B':8, 'P':2, 'C':2},
	#{'N':0, 'B':8, 'P':3, 'C':3},

	 # N=50, B=8
        #{'N':50, 'B':8, 'P':1, 'C':1},
        #{'N':50, 'B':8, 'P':1, 'C':2}, 
        #{'N':50, 'B':8, 'P':1, 'C':3}, 

        #{'N':50, 'B':8, 'P':2, 'C':1}, 
        #{'N':50, 'B':8, 'P':3, 'C':1}, 

        #{'N':50, 'B':8, 'P':2, 'C':2},
        #{'N':50, 'B':8, 'P':3, 'C':3},
        #############################
        # N=100, B=8
        #{'N':100, 'B':8, 'P':1, 'C':1},
        #{'N':100, 'B':8, 'P':1, 'C':2}, 
        #{'N':100, 'B':8, 'P':1, 'C':3}, 

        #{'N':100, 'B':8, 'P':2, 'C':1}, 
        #{'N':100, 'B':8, 'P':3, 'C':1}, 

        #{'N':100, 'B':8, 'P':2, 'C':2},
        #{'N':100, 'B':8, 'P':3, 'C':3},
        #############################
        # N=150, B=8
        #{'N':150, 'B':8, 'P':1, 'C':1},
        #{'N':150, 'B':8, 'P':1, 'C':2}, 
        #{'N':150, 'B':8, 'P':1, 'C':3},  

        #{'N':150, 'B':8, 'P':2, 'C':1}, 
        #{'N':150, 'B':8, 'P':3, 'C':1}, 

        #{'N':150, 'B':8, 'P':2, 'C':2},
        #{'N':150, 'B':8, 'P':3, 'C':3},
        #############################
        # N=200, B=8
        #{'N':200, 'B':8, 'P':1, 'C':1},
        #{'N':200, 'B':8, 'P':1, 'C':2}, 
        #{'N':200, 'B':8, 'P':1, 'C':3}, 

        #{'N':200, 'B':8, 'P':2, 'C':1}, 
        #{'N':200, 'B':8, 'P':3, 'C':1}, 

        #{'N':200, 'B':8, 'P':2, 'C':2},
        #{'N':200, 'B':8, 'P':3, 'C':3},
        #############################
        # N=200, B=8
        #{'N':250, 'B':8, 'P':1, 'C':1},
        #{'N':250, 'B':8, 'P':1, 'C':2}, 
        #{'N':250, 'B':8, 'P':1, 'C':3}, 

        #{'N':250, 'B':8, 'P':2, 'C':1}, 
        #{'N':250, 'B':8, 'P':3, 'C':1}, 

        #{'N':250, 'B':8, 'P':2, 'C':2},
        #{'N':250, 'B':8, 'P':3, 'C':3},
        #############################
        # N=300, B=8
        #{'N':300, 'B':8, 'P':1, 'C':1},
        #{'N':300, 'B':8, 'P':1, 'C':2}, 
        #{'N':300, 'B':8, 'P':1, 'C':3}, 

        #{'N':300, 'B':8, 'P':2, 'C':1}, 
        #{'N':300, 'B':8, 'P':3, 'C':1}, 

#        {'N':300, 'B':8, 'P':2, 'C':2},
#        {'N':300, 'B':8, 'P':3, 'C':3},
        #############################
        # N=350, B=8
 #       {'N':350, 'B':8, 'P':1, 'C':1},
 #       {'N':350, 'B':8, 'P':1, 'C':2}, 
 #       {'N':350, 'B':8, 'P':1, 'C':3}, 

  #      {'N':350, 'B':8, 'P':2, 'C':1}, 
  #      {'N':350, 'B':8, 'P':3, 'C':1}, 

   #     {'N':350, 'B':8, 'P':2, 'C':2},
   #     {'N':350, 'B':8, 'P':3, 'C':3},
        #############################
        # N=398, B=8
   #     {'N':398, 'B':8, 'P':1, 'C':1},
   #     {'N':398, 'B':8, 'P':1, 'C':2}, 
   #     {'N':398, 'B':8, 'P':1, 'C':3},  
        
   #     {'N':398, 'B':8, 'P':2, 'C':1}, 
   #     {'N':398, 'B':8, 'P':3, 'C':1},  

    #    {'N':398, 'B':8, 'P':2, 'C':2}, 
    #    {'N':398, 'B':8, 'P':3, 'C':3},

	#############################
	# N=150, varying producers
	#{'N':150, 'B':8, 'P':1, 'C':1},
	#{'N':150, 'B':8, 'P':2, 'C':1},
	#{'N':150, 'B':8, 'P':3, 'C':1},
	#{'N':150, 'B':8, 'P':4, 'C':1},
	#{'N':150, 'B':8, 'P':5, 'C':1},
	#{'N':150, 'B':8, 'P':10, 'C':1},
	#{'N':150, 'B':8, 'P':15, 'C':1},
	#{'N':150, 'B':8, 'P':20, 'C':1},
	#{'N':150, 'B':8, 'P':25, 'C':1},
	#{'N':150, 'B':8, 'P':30, 'C':1},
	#{'N':150, 'B':8, 'P':35, 'C':1},
	#{'N':150, 'B':8, 'P':40, 'C':1},
	#{'N':150, 'B':8, 'P':45, 'C':1},
	#{'N':150, 'B':8, 'P':50, 'C':1},
	#{'N':150, 'B':8, 'P':55, 'C':1},

	#############################
	# N=150, varying consumers
	#{'N':150, 'B':8, 'P':1, 'C':1},
	#{'N':150, 'B':8, 'P':1, 'C':2},
	#{'N':150, 'B':8, 'P':1, 'C':3},
	#{'N':150, 'B':8, 'P':1, 'C':4},	
	#{'N':150, 'B':8, 'P':1, 'C':5},
	#{'N':150, 'B':8, 'P':1, 'C':10},
	#{'N':150, 'B':8, 'P':1, 'C':15},
	#{'N':150, 'B':8, 'P':1, 'C':20},
	#{'N':150, 'B':8, 'P':1, 'C':25},
	#{'N':150, 'B':8, 'P':1, 'C':30},
	#{'N':150, 'B':8, 'P':1, 'C':35},
	#{'N':150, 'B':8, 'P':1, 'C':40},
	#{'N':150, 'B':8, 'P':1, 'C':45},
	#{'N':150, 'B':8, 'P':1, 'C':50},
	#{'N':150, 'B':8, 'P':1, 'C':55},

	############################
	# No producers
	#{'N':100, 'B':8, 'P':0, 'C':1},
	#{'N':100, 'B':8, 'P': -1, 'C':2},
	#{'N':100, 'B':8, 'P':0, 'C':0},

	############################
	# No Consumers   
	#{'N':100, 'B':8, 'P':1, 'C':0},
	#{'N':100, 'B':8, 'P':1, 'C': -1},
    ]
    i = 1
    for t in test_cases:
        print 'Test Case: {}/{}'.format(i, len(test_cases))
        i += 1
        call_produce(PROG, '{} {} {} {}'.format(t['N'], t['B'], t['P'], t['C']), X)
        print ''

def generate_stats_table():
    '''
    Converts the raw times in `times` into a text table 
    containing the average time and the standard deviation.
    '''
    with open('lab3-stats.csv', 'w') as file:
        file.write("N,B,P,C,Average Time (ms),Standard Deviation (ms)\n")

        for t in times:
            avg = sum(t['times']) / float(len(t['times']))
            std = sqrt(float(reduce(lambda x, y: x + y, map(lambda x: (x - avg) ** 2, t['times']))) / float(len(t['times'])))

            k = t['cmd'].split()
            file.write('{},{},{},{},{},{}\n'.format(k[0],k[1],k[2],k[3], avg, std))
    print 'Written the statistics out to lab3-stats.csv'

def dump_raw_times():
    '''
    Writes the raw times to a csv file
    '''
    with open('lab3-times.csv', 'w') as file:
        for k in times:
            t = str(k['times'])
            file.write('{},{}\n'.format(k['cmd'],t[1:-1]))
    print 'Written the raw times out to lab3-times.csv'

def main():
    generate_test_data()
    print '='*50
    generate_stats_table()
    dump_raw_times()



if __name__ == '__main__':
    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    os.chdir(dname)
    main()
