#include <iostream>
#include <cmath>

// EUROPEAN OPTIONS

// Black Scholes Formula = C0 = ( S0 )( N( d1 ) ) − ( X )( e ) - > to the power - > ( − r T )( N( d2 ) )
// d1 = ( ( ( ln ( S0 / X ) ) + ( r + ( ( ( sigma ) - > to the power - > ( 2 ) ) / 2 ) ) ( T ) ) ) / ( sigma ( square root T ) )
// d2 = ( d1 ) - ( sigma ( square root T ) )

// C0  is the value of the call option at time 0.
// S0: the value of the underlying stock at time 0.
// N(): the cumulative standard normal density function - the probability that the option will be at the money when the expiry time comes
// X: the exercise or strike price.


// r: the risk-free interest rate (annualized).
// T: the time until option expiration in years.
// σ: the annualized standard deviations of log returns. ( Volatility )
// e and ln are the exponential and natural log functions respectively

// PUT PRICE = CALL PRICE - UNDERLYING + ( STRIKE PRICE / ( 1 + RISK FREE RATE ) ** TIME )

// Calculates The Normal Probability Density Function
double norm_pdf( const double & value ) {
    return ( 1.0 / ( pow( 2 * M_PI , 0.5 ) ) ) * exp( - 0.5 * value * value ) ;
}

// Calculates The Normal Cumulative Distribution Automatically
// Erfc Is The Gaussian Error Function And It Is Related To The Normal Cumulative Distribution
double norm_cdf( const double & value )
{
   return 0.5 * erfc( - value * M_SQRT1_2 ) ;
}

double d_1( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    double natural_log_of_the_current_difference =  log( underlying_price / strike_price ) ;
    double rest_of_the_top_line_equation = ( risk_free_rate + ( pow( volatility , 2  ) / 2 ) ) * time  ;
    double volatility_times_square_root_of_time = volatility * sqrt( time ) ;
    return ( natural_log_of_the_current_difference + rest_of_the_top_line_equation ) / volatility_times_square_root_of_time ;
}

double d_2( double d_1 , double volatility , double time ) {
    //
    return d_1 - ( volatility * sqrt( time ) ) ;
}

double calculate_call_price( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double d2 = d_2( d1 , volatility , time ) ;
    double left_hand_side = underlying_price * norm_cdf( d1 ) ;


    double right_hand_side = strike_price * exp( risk_free_rate * time * ( - 1 ) ) * norm_cdf( d2 ) ;
    return left_hand_side - right_hand_side ;
    //
}

double calculate_put_price( double call_price , double underlying_price , double strike_price , double risk_free_rate , double time ) {
    return call_price - underlying_price + ( strike_price / pow( 1 + risk_free_rate , time ) ) ;
}

// CALL DELTA = N( D1 )
double calculate_call_delta( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    return norm_cdf( d1 ) ;
}

// PUT DELTA = N( D1 ) - 1
double calculate_put_delta( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    return norm_cdf( d1 ) - 1 ;
}

// CALL GAMMA = N'( d1 ) / S * sigma * square_root( T )
double calculate_call_gamma( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double upper_part = norm_pdf( d1 ) ;
    double lower_part = underlying_price * volatility * ( sqrt( time ) ) ;
    return upper_part / lower_part ;
}

// IDENTICAL TO THE CALL GAMMA BECAUSE OF THE PUT CALL PARITY
double calculate_put_gamma( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    return calculate_call_gamma( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
}

// CALL VEGA = SN'( d1 ) * square_root( time )
double calculate_call_vega( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double first_part = underlying_price * norm_pdf( d1 ) ;
    double second_part = sqrt( time ) ;
    return first_part * second_part ;
}

// IDENTICAL TO THE PUT VEGA BECAUSE OF THE PUT CALL PARITY
double calculate_put_vega( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    return calculate_call_vega( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
}



double calculate_call_theta( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double d2 = d_2( d1 , volatility , time ) ;
    double first_part = ( ( underlying_price * norm_pdf( d1 ) * volatility ) / 2 * sqrt( time ) ) * - 1 ;
    double second_part = ( risk_free_rate * strike_price * exp( risk_free_rate * time * ( - 1 ) ) * norm_cdf( d2 ) ) ;
    return first_part - second_part ;
}

double calculate_put_theta( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double d2 = d_2( d1 , volatility , time ) ;
    double first_part = ( ( underlying_price * norm_pdf( d1 ) * volatility ) / 2 * sqrt( time ) ) * - 1 ;
    double second_part = ( risk_free_rate * strike_price * exp( risk_free_rate * time * ( - 1 ) ) * norm_cdf( ( d2 * ( - 1 ) ) ) ) ;
    return first_part + second_part ;
}

double calculate_call_rho( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double d2 = d_2( d1 , volatility , time ) ;
    double first_part = strike_price * time ;
    double second_part = exp( risk_free_rate * time * ( - 1 ) ) * norm_cdf( d2 ) ;
    return first_part * second_part ;
}

double calculate_put_rho( double underlying_price , double strike_price , double risk_free_rate , double volatility , double time ) {
    //
    double d1 = d_1( underlying_price , strike_price , risk_free_rate , volatility , time ) ;
    double d2 = d_2( d1 , volatility , time ) ;
    double first_part = ( strike_price * time ) * ( - 1 ) ;
    double second_part = exp( risk_free_rate * time * ( - 1 ) ) * norm_cdf( d2 * ( - 1 ) ) ;
    return first_part * second_part ;
}

