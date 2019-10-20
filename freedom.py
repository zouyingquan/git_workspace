import xlrd
import xlwt

def file_write(data,filename,sheetname):
	wt = xlwt.Workbook()
	write_sheet = wt.add_sheet(sheetname)
	for i in range(len(data)):
		for j in range(len(data[i])):
			write_sheet.write(i, j,data[i][j])
	
	wt.save(filename)

def data_calc(level,target_percentage,buying_price,buying_num,selling_num):
	selling_price = buying_price * (1 + target_percentage)
	profit = (selling_price * selling_num) - (buying_price * buying_num)
	profit_rate = profit / (buying_price * buying_num)
	buying_total_price = (buying_price * buying_num)
	selling_total_price = (selling_price * selling_num)
	data = [level,round(buying_price,3),round(selling_price,3),buying_num,selling_num,round(buying_total_price,2),round(selling_total_price,2),round(profit,2),profit_rate]
	return data
	
filename = '中欧新蓝筹混合A.xlsx'
buying_price = 1.4461

#filename = '易方达消费行业股票.xlsx'
#buying_price = 2.964

title = ['档位','买入价格','卖出价格','买入数量','卖出数量','买入金额','卖出金额','盈利金额','盈利比例']
level = 1
target_percentage = 0.03

buying_num = 300
selling_num = 300

data_list = []
data_list.append(title)

for level in range(1,10):
	data = data_calc(level,target_percentage,buying_price,buying_num,selling_num)
	buying_price = buying_price * (1 - target_percentage)
	data_list.append(data)
	

file_write(data_list,filename,'3%')
	
