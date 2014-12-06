// Compatiblity layer with ibex for the simple interval library from Luc JAULIN, with minor modifications from Fabrice LE BARS and Jeremy NICOLA.

#ifndef __INTERVAL__
#define __INTERVAL__

#ifdef _MSC_VER
// Disable some Visual Studio warnings.
#	ifndef CRT_SECURE_NO_DEPRECATE
#		define CRT_SECURE_NO_DEPRECATE
#	endif // CRT_SECURE_NO_DEPRECATE
#	ifndef _CRT_SECURE_NO_WARNINGS
#		define _CRT_SECURE_NO_WARNINGS
#	endif // _CRT_SECURE_NO_WARNINGS
//#	ifndef _CRT_NONSTDC_NO_WARNINGS
//#		define _CRT_NONSTDC_NO_WARNINGS
//#	endif // _CRT_NONSTDC_NO_WARNINGS
#endif // _MSC_VER

#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "iboolean.h"

// min, max, MIN, MAX, ERROR may need to be undefined for ibex...
#pragma push_macro("ERROR")
#pragma push_macro("MAX")
#pragma push_macro("MIN")
#pragma push_macro("max")
#pragma push_macro("min")

#ifndef PREVENT_MACROS_UNDEF_IBEX
#ifdef min
#undef min
#endif // min
#ifdef max
#undef max
#endif // max
#ifdef MIN
#undef MIN
#endif // MIN
#ifdef MAX
#undef MAX
#endif // MAX
#ifdef ERROR
#undef ERROR
#endif // ERROR
#endif // PREVENT_MACROS_UNDEF_IBEX

#ifdef _MSC_VER
// Disable some Visual Studio warnings that happen sometimes in ibex.
#pragma warning(disable : 4018) 
#pragma warning(disable : 4065) 
#pragma warning(disable : 4068) 
#pragma warning(disable : 4100) 
#pragma warning(disable : 4101) 
#pragma warning(disable : 4127) 
#pragma warning(disable : 4189) 
#pragma warning(disable : 4244)
#pragma warning(disable : 4245)
#pragma warning(disable : 4250)
#pragma warning(disable : 4290)
#pragma warning(disable : 4505)
#pragma warning(disable : 4512)
#pragma warning(disable : 4702)
#pragma warning(disable : 4715)
#pragma warning(disable : 4805)
#pragma warning(disable : 4996)
#endif // _MSC_VER

#ifdef __GNUC__
// Disable some GCC warnings that happen sometimes in ibex.
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#pragma GCC diagnostic push
#else
#pragma GCC diagnostic ignored "-Wpragmas"
#endif // (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#endif // __GNUC__

#include "ibex.h"

#ifdef __GNUC__
// Restore the GCC warnings previously disabled for ibex.
#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#pragma GCC diagnostic pop
#else
#pragma GCC diagnostic warning "-Wpragmas"
#pragma GCC diagnostic warning "-Wunknown-pragmas"
#pragma GCC diagnostic warning "-Wunused-variable"
#pragma GCC diagnostic warning "-Wunused-parameter"
#endif // (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#endif // __GNUC__

#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled for ibex.
#pragma warning(default : 4996)
#pragma warning(default : 4805)
#pragma warning(default : 4715)
#pragma warning(default : 4702)
#pragma warning(default : 4512)
#pragma warning(default : 4505)
#pragma warning(default : 4290)
#pragma warning(default : 4250)
#pragma warning(default : 4245)
#pragma warning(default : 4244)
#pragma warning(default : 4189) 
#pragma warning(default : 4127) 
#pragma warning(default : 4101) 
#pragma warning(default : 4100) 
#pragma warning(default : 4068) 
#pragma warning(default : 4065) 
#pragma warning(default : 4018) 
#endif // _MSC_VER

// Restore the macros previously undefined for ibex...
#pragma pop_macro("min")
#pragma pop_macro("max")
#pragma pop_macro("MIN")
#pragma pop_macro("MAX")
#pragma pop_macro("ERROR")

#ifdef _MSC_VER
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif // UNREFERENCED_PARAMETER
#endif // _MSC_VER

#ifdef __GNUC__
#undef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (void)(P)
#endif // __GNUC__

#ifdef __BORLANDC__
#undef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) 
#endif // __BORLANDC__

// To avoid Visual Studio 2013 warning about overflow in floating-point constant arithmetic 
// each time INFINITY or NAN is used.
#if (_MSC_VER >= 1800)
#pragma warning(disable : 4056)
#endif // (_MSC_VER >= 1800)

// To avoid Visual Studio warnings that would happen for any project using ibex. 
#ifdef _MSC_VER
#pragma warning(disable : 4505)
#pragma warning(disable : 4512)
#endif // _MSC_VER

// To avoid Visual Studio warnings that would happen for any project using interval. 
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif // _MSC_VER

#ifndef INFINITY
#define INFINITY HUGE_VAL
#endif // INFINITY

#if defined(_MSC_VER) || defined(__BORLANDC__) 
// Used to define NAN (Not A Number).
#ifndef NAN
extern const unsigned long nan[2];
extern const double nan_double;
#define NAN nan_double
#define NAN_CONSTS_NEEDED
#endif // NAN
#endif // defined(_MSC_VER) || defined(__BORLANDC__) 

// Infinity is denoted by oo.
#ifndef oo
//#define oo 1.0/0.0
//#define oo 1000000000.0
//#define oo INFINITY
#define oo POS_INFINITY
#endif // oo

// Try to transform the default interval constructor so that it returns an empty interval instead of [-oo,oo]...
//inline ibex::Interval empty_default_interval() { return ibex::Interval(ibex::Interval::EMPTY_SET); }
//#define interval() ibex::Interval(ibex::Interval::EMPTY_SET)
class interval_empty_default : public ibex::Interval 
{
public:
	interval_empty_default() : ibex::Interval(ibex::Interval::EMPTY_SET) { }
	interval_empty_default(const ibex::Interval& _i) : ibex::Interval(_i) { }
	interval_empty_default(double a, double b) : ibex::Interval(a, b) { }
	interval_empty_default(double a) : ibex::Interval(a) { }
	//operator const ibex::Interval&() const { return *this; }
};

// Needed because of errors : overloads have similar conversions...
// Should be friend?
inline interval_empty_default operator*(const interval_empty_default& x1, const interval_empty_default& x2) { return ibex::Interval(x1)*ibex::Interval(x2); }
inline interval_empty_default operator*(const ibex::Interval& x1, const interval_empty_default& x2) { return ibex::Interval(x1)*ibex::Interval(x2); }
inline interval_empty_default operator*(const interval_empty_default& x1, const ibex::Interval& x2) { return ibex::Interval(x1)*ibex::Interval(x2); }
inline interval_empty_default operator*(const double& x1, const interval_empty_default& x2) { return x1*ibex::Interval(x2); }
inline interval_empty_default operator*(const interval_empty_default& x1, const double& x2) { return ibex::Interval(x1)*x2; }

// interval will be noted as before...
#define interval interval_empty_default
//#define interval ibex::Interval

// To be able to use Interval like in ibex... However this might be confusing as ibex::Interval does not 
// have the same default constuctor as interval...
//#define Interval interval_empty_default

// In some cases you might need to disable totally the following defines.
// However, most of the time it should be possible to use e.g. #undef isEmpty where appropriate when 
// there are conflicts, as well as including this header at last (this happens sometimes with Qt)...
#ifndef DISABLE_DEFINES_OLD_INTERVAL_CLASS_VARIABLES
#define inf lb()
#define sup ub()
#define isEmpty is_empty()
#endif // DISABLE_DEFINES_OLD_INTERVAL_CLASS_VARIABLES

// Used to define NAI (Not An Interval).
#ifndef NAI
extern const interval nai;
#define NAI nai
#define NAI_CONST_NEEDED
#endif // NAI

using namespace std;

// Include <QDataStream> and <QDebug> before this file to be able to use Qt specific features if you have Qt.
#ifdef QT_VERSION 
class QDataStream;
class QDebug;
#else
#define qDebug() std::cout
#endif // QT_VERSION 

// Deprecated.
typedef double reel;

//----------------------------------------------------------------------
// Useful real-valued functions
//----------------------------------------------------------------------
double Min(vector<double>& x);
double Max(vector<double>& x);
double Sign(const double x);
double Chi(const double a, const double b, const double c);
double Arccossin(const double x, const double y);
double Arg(const double x, const double y);
double Det(double ux, double uy, double vx, double vy);
double DistanceDirSegment(double mx, double my, double theta, double ax, double ay, double bx, double by);
void DistanceDirSegment(double& d, double& phi, double mx, double my, double theta, double ax, double ay, double bx, double by);
double DistanceDirSegments(double mx, double my, double theta, 
						   vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
void DistanceDirSegments(double& d, double& phi, double mx, double my, double theta, 
						 vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
#define DistanceDirCercle DistanceDirCircle
#define DistanceDirCercles DistanceDirCircles
double DistanceDirCircle(double mx, double my, double theta, double cx, double cy, double r);
void DistanceDirCircle(double& d, double& phi, double mx, double my, double theta, double cx, double cy, double r);
double DistanceDirCircles(double mx, double my, double theta, vector<double> cx, vector<double> cy, vector<double> r);
void DistanceDirCircles(double& d, double& phi, double mx, double my, double theta, 
						vector<double> cx, vector<double> cy, vector<double> r);
double DistanceDirSegmentsOrCircles(double mx, double my, double theta,
									vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by,
									vector<double> cx, vector<double> cy, vector<double> r);
void DistanceDirSegmentsOrCircles(double& d, double& phi, double mx, double my, double theta,
								  vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by,
								  vector<double> cx, vector<double> cy, vector<double> r);
//----------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------
//std::ostream& operator<<(std::ostream& os, const interval& a);
#ifdef QT_VERSION 
//inline QDataStream& operator<<(QDataStream& s, const interval& i)
//{
//	s << i.lb() << i.ub() << i.is_empty();
//	return s;
//}
//
//inline QDataStream& operator>>(QDataStream& s, interval& i)
//{
//	s >> i.lb() >> i.ub() >> i.is_empty();
//	return s;
//}

inline QDebug operator<<(QDebug os, const interval& a)
{
	if (a.is_empty()) os.nospace() << "EmptyInterval";
	else if (a.lb() != a.ub())
	{ 
		os.nospace() << "[" << a.lb() << ", " << a.ub() << "] "; 
	}
	else os.nospace() << a.lb();
	return os.space();
}
#endif // QT_VERSION 
//----------------------------------------------------------------------
// Interval-valued functions
//----------------------------------------------------------------------
interval Min(const interval& x, const interval& y);
interval Min(const interval& x, const interval& y, const interval& z);
interval Max(const interval& x, const interval& y);
interval Max(const interval& x, const interval& y, const interval& z);
#define Abs ibex::abs
#define Sqr ibex::sqr
#define Sqrt ibex::sqrt
interval InvSqrt(interval& X);
#define Exp ibex::exp
#define Log ibex::log
#define Pow ibex::pow
//interval Pow(const interval& x, int num, int den);
interval PowFrac(const interval& x, int num, int den);
interval PowRoot(const interval& x, int num, int den);
#define Cos ibex::cos
#define Sin ibex::sin
#define Tan ibex::tan
#define Acos ibex::acos
#define Asin ibex::asin
#define Atan ibex::atan
interval Det(interval&, interval&, interval&, interval&);
interval Det(interval& ux, interval& uy, double& vx, double& vy);
interval Step(const interval&);
interval Parabole(const interval&, double, double, double);
interval Inter(const interval&, const interval&);
interval Inter(vector<interval> x);
interval Union(const interval&, const interval&);
interval Union(vector<interval> x);
interval Inflate(const interval&, double);
//----------------------------------------------------------------------
// Other functions
//----------------------------------------------------------------------
double Inf(const interval&);
double Sup(const interval&);
double Center(const interval&);
double Width(const interval&);
#define ToReel ToReal
#define Todouble ToReal
double ToReal(const interval&);
bool Disjoint(const interval& a, const interval& b);
bool Subset(const interval& a, const interval& b);
bool SubsetStrict(const interval& a, const interval& b);
iboolean In(const interval&, const interval&);
bool In(double, const interval&);
//----------------------------------------------------------------------
// Contractors
//----------------------------------------------------------------------
#define Cplus Cadd
void Cadd(interval& Z, interval& X, interval& Y, int sens = 0);
void Cadd(interval& Z, double x, interval& Y, int sens = 0);
void Cadd(interval& Z, interval& X, double y, int sens = 0);
//void Cadd(double z, interval& X, interval& Y, int sens = 0);
#define Cmoins Csub
void Csub(interval& Z, interval& X, interval& Y, int sens = 0);
void Csub(interval& Z, double x, interval& Y, int sens = 0);
void Csub(interval& Z, interval& X, double y, int sens = 0);
//void Csub(double z, interval& X, interval& Y, int sens = 0);
#define Cprod Cmul
void Cmul(interval& Z, interval& X, interval& Y, int sens = 0);
void Cmul(interval& Z, double x, interval& Y, int sens = 0);
void Cmul(interval& Z, interval& X, double y, int sens = 0);
//void Cmul(double z, interval& X, interval& Y, int sens = 0);
void Cdiv(interval& Z, interval& X, interval& Y, int sens = 0);
#define Cegal Cequal
void Cequal(interval& Y, interval& X, int sens);
void Cequal(interval& Y, interval& X);
void Cmin(interval& a, interval& b, interval& c, int sens = 0);
void Cmin(interval& a, interval& b, interval& c, interval& d, int sens = 0);
void Cmin(interval& a, interval& b, interval& c, interval& d, interval& e, int sens = 0);
int Cmin(interval& a, vector<interval>& x, int sens = 0);
void Cmax(interval& a, interval& b, interval& c, int sens = 0);
void Cabs(interval& Y, interval& X, int sens = 0);
#define Csame_sign Csign
void Csign(interval& Y, interval& X);
void Csign(interval& Y, interval& X, int sens, double a = 0);
void Cchi(interval& F, interval& A, interval& B, interval& C);
void Cgeq(interval& Y, interval& X);
void Cinteger(interval&);
void Cboolean(interval&);
void Csqr(interval& Y, interval& X, int sens = 0);
void Cexp(interval& Y, interval& X, int sens = 0);
void Clog(interval& Y, interval& X, int sens = 0);
void Cpow(interval& Y, interval& X, int n);
void Ccos(interval& Y, interval& X, int sens = 0);
void Csin(interval& Y, interval& X, int sens = 0);
void Ctan(interval& Y, interval& X, int sens = 0);
void Catan(interval& Y, interval& X, int sens = 0);
//CAngle() bStrongAngle?
#define CNorm Cnorm
void Cnorm(interval& N, interval& X, interval& Y);
void Cnorm(interval& N, interval& X, interval& Y, interval& Z, int sens);
#define CScal Cscal
void Cscal(interval& s, interval& ux, interval& uy, interval& vx, interval& vy);
void Cscal(interval& s, double& ux, double& uy, interval& vx, interval& vy);
#define CDet Cdet
void Cdet(interval& det, interval& ux, interval& uy, interval& vx, interval& vy, int sens = 0);
void Cdet(interval& det, double& ux, double& uy, interval& vx, interval& vy, int sens = 0);
void Cdet(interval& det, interval& ux, interval& uy, double& vx, double& vy, int sens = 0);
void Cstep(interval& Y, interval& X);
void Cstep(interval& Y, interval& X, int sens, double a = 0);
void Cramp(interval& Y, interval& X, int sens = 0, double a = 0);
void Cheaviside(interval& Y, interval& X, int sens = 0, double a = 0);
void Crect(interval& Z, interval& X, interval& Y, int sens = 0);
void Crect(interval& Y, interval& X, int sens = 0);
void Ctriangle(interval& Y, interval& X, int sens = 0);
void CDistanceDirLine(interval& dist, interval& mx, interval& my, interval& theta, 
					  double& ax, double& ay, double& bx, double& by);
int CDistanceDirSegment(interval& dist, interval& mx, interval& my, interval& theta, 
						double ax, double ay, double bx, double by, int sens = 0);
void CDistanceDirSegments(interval& distmin, interval& mx, interval& my, interval& theta, 
						  vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
void CPointInLine(interval& mx, interval& my, double& ax, double& ay, double& bx, double& by);
#define CinSegment CPointInSegment
void CPointInSegment(interval& mx, interval& my, double ax, double ay, double bx, double by);
#define CinSegments CPointInSegments
void CPointInSegments(interval& mx, interval& my, vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
#define CinCircle CPointInCircle
void CPointInCircle(interval& mx, interval& my, double cx, double cy, double r);
#define CinCircles CPointInCircles
void CPointInCircles(interval& mx, interval& my, vector<double> cx, vector<double> cy, vector<double> r, bool truth = true);
#define CinSegmentsOrCircles CPointInSegmentsOrCircles
void CPointInSegmentsOrCircles(interval& mx, interval& my, 
							   vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
							   vector<double> cx, vector<double> cy, vector<double> r);
void CPointOutsideSegment(interval& mx, interval& my, double& ax, double& ay, double& bx, double& by, bool outer);
void CPointOutsideSegments(interval& mx, interval& my, 
						   vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, bool outer);
void CPoseInSegment(interval& mx, interval& my, interval& phi, double& ax, double& ay, double& bx, double& by);
void CPoseInSegments(interval& mx, interval& my, interval& phi, 
					 vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
void CPoseInCircle(interval& mx, interval& my, interval& phi, double& cx, double& cy, double& r);
void CPoseInCircles(interval& mx, interval& my, interval& phi, vector<double> cx, vector<double> cy, vector<double> r);
void CPoseInSegmentsOrCircles(interval& mx, interval& my, interval& malpha, 
							  vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
							  vector<double> cx, vector<double> cy, vector<double> r);
void CPoseTrans(interval& qx, interval& qy, interval& d, interval& px, interval& py, interval& theta);  //Go straight
void CPoseRotTrans(interval& qx, interval& qy, interval& beta, interval& phi, interval& d, interval& px, interval& py, interval& alpha);
void CPoseTransInWallsOrCircles(interval& px, interval& py, interval& alpha, interval& d, 
								vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
								vector<double> cx,vector<double> cy, vector<double> r);
void CPoseTransRotInWallsOrCircles(interval& px, interval& py, interval& alpha, interval& d, interval& psi, 
								   vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
								   vector<double> cx, vector<double> cy, vector<double> r);
void CPoseRotTransRotInWallsOrCircles(interval& px, interval& py, interval& alpha, interval& phi, interval& d, interval& psi, 
									  vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
									  vector<double> cx, vector<double> cy, vector<double> r);
void CPoseRotTransPointInWallsOrCircles(interval& px, interval& py, interval& alpha, interval& phi, interval& d, 
										vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
										vector<double> cx, vector<double> cy, vector<double> r);
void CPoseTransPointInWall(interval& px,interval& py, interval& alpha, interval& d, 
						   double ax, double ay, double bx, double by, bool truth = true);
void CPoseTransPointInWalls(interval& px,interval& py, interval& alpha, interval& d0, 
							vector<double>& ax, vector<double>& ay, vector<double>& bx, vector<double>& by, bool truth = true);
void CPoseTransPointInWallsOrCircles(interval& px,interval& py, interval& alpha, interval& d0, 
									 vector<double> ax,vector<double> ay,vector<double> bx,vector<double> by, 
									 vector<double> cx, vector<double> cy, vector<double> r, bool truth = true);
void CPoseTowardSegment(interval& mx, interval& my, interval& theta, 
						double& ax, double& ay, double& bx, double& by, bool truth = true);
#define Ccroisepas Cnocross
void Cnocross(interval& px, interval& py, interval& mx, interval& my, double& ax, double& ay, double& bx, double& by);
#define CPatteCroiseAucunSegment CLegCrossNoSegment
void CLegCrossNoSegment(interval& dist, interval& px, interval& py, interval& theta, 
						vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
void CLegOnWalls(interval& dist, interval& px, interval& py, interval& theta, 
				 vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
void CLegOnWallsOrCircles(interval& dist, interval& px, interval& py, interval& theta, 
						  vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, 
						  vector<double> cx, vector<double> cy, vector<double> r);
void ShowContraction(interval&, interval&, interval&, interval&);
void IntButterfly(interval& Y, interval Yo, interval dY, interval& X, interval Xo, int sens);
void Inter1(interval&, interval&, const interval&, const interval&, const interval&);
void Sucre(interval&, const interval&);
void Cnotin(interval& X, interval& Y);
void C_q_in(interval& x, int q, vector<interval>& y);
//----------------------------------------------------------------------
// Separators
//----------------------------------------------------------------------
void SinRing(interval& X, interval& Y, double cx, double cy, interval R, bool outer);
//----------------------------------------------------------------------
// Other
//----------------------------------------------------------------------
void diffI(interval &x0, interval &x1, interval &c0, interval &c1);
iboolean TestDiskExists(const interval& X, const interval& Y, const interval& P1, const interval& P2, const interval& P3);
iboolean TestDiskForall(const interval& X, const interval& Y, const interval& P1, const interval& P2, const interval& P3);

#endif // __INTERVAL__
