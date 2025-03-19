import tkinter as tk
from tkinter import *
class RepaymentCalculator:
    def __init__(self):
        self.window = Tk()
        self.window.title("算完壓力好大")
        
        self.rate_var = StringVar()
        self.year_var = StringVar()
        self.loan_var = StringVar()
        self.month_var = StringVar()
        self.repayment_var = StringVar()
        
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        row = 0
        labelText_EntryTextVariable = [("Rate",self.rate_var), ("Year",self.year_var), ("Loan Money", self.loan_var)]
        for (labelText, EntryTextVariable) in labelText_EntryTextVariable:    
            Label(self.window, text=labelText, anchor="w", padx=5).grid(row=row, column=0, sticky="w")
            Entry(self.window, textvariable=EntryTextVariable, justify="right").grid(row=row, column=1)
            row = row + 1
        
        for (key, value) in [("Month", self.month_var), ("Repayment",self.repayment_var)]:
            Label(self.window, text=key, anchor="w", padx=5).grid(row=row, column=0, sticky="w")
            Label(self.window, textvariable=value, anchor="e").grid(row=row, column=1, sticky="e")
            row = row + 1
        
        Button(self.window, text="Calculate", command=self.calculate).grid(row=5, column=1)
    
    def calculate(self):
        try:
            rate = float(self.rate_var.get()) / 100 /    12
            years = int(self.year_var.get())
            loan = float(self.loan_var.get())
            months = years * 12
            
            if(rate != 0):            
                monthly_payment = int((loan * rate) / (1 - (1 / (1 + rate) ** months)))
            else:
                monthly_payment = int(loan * rate)
                
            repayment = monthly_payment * months

            self.month_var.set(f"{int(monthly_payment)}")
            self.repayment_var.set(f"{int(repayment)}")
        
        except ValueError:
            self.month_var.set("Error")
            self.repayment_var.set("Error")
    
    
if __name__ == "__main__":
    repaymentCalculator = RepaymentCalculator()
    repaymentCalculator.start()