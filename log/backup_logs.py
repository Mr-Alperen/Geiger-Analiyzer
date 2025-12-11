import shutil
import datetime

src = 'log/geiger_log.txt'
backup_dir = 'log/backup/'

date = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
dst = f"{backup_dir}geiger_log_{date}.txt"

shutil.copy(src, dst)
print(f"Log yedeklendi: {dst}")